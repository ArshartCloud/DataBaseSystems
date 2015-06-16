#include "catalog.h"
#include "read.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int padding = 20;
#define MAXN 300 //  the maximum input length;

catalog::catalog(void) {
    head = new attribute;
    tail = new attribute;
    head->pre = NULL;
    head->next = tail;
    tail->pre = head;
    tail->next = NULL;
    count = 0;
}

catalog::~catalog(void) {
    attribute* last;
    for (int i = 0; i < count; i++) {
        last = tail->pre;
        delete[] last->key_name;
        delete[] last->key_type;
        tail->pre = tail->pre->pre;
        delete last;
    }
    delete head;
    delete tail;

    //release arr
    int size = arr.getSize();
    for (int i = 0; i < size; i++) {
        tuple_release((arr[i]));
    }
    arr.vector_release();
}

void catalog::print(void) {
    // heading
    cout << setfill(' ') << left
         << setw(padding) << "_id"
         << setw(padding) << "Key_name"
         << setw(padding) << "Key_type"
         << setw(padding) << "count"
         << endl;
    // key records
    attribute* cur = head->next;
    for (int i = 0; i < count; i++) {
        cout << setw(padding) << cur->_id
             << setw(padding) << cur->key_name
             << setw(padding) << cur->key_type
             << setw(padding) << cur->count
             << endl;
        cur = cur->next;
    }
    return;
}

int catalog::index(char* key_type, char* key_name) {
    attribute *p = search(key_type, key_name);
    if (p != NULL) {
        ++p->count;
    } else {
        p = new attribute;
        p->_id = ++count;
        p->key_type = new char[strlen(key_type) + 1];
        strncpy(p->key_type, key_type, strlen(key_type));
        p->key_type[strlen(key_type)] = '\0';

        p->key_name = new char[strlen(key_name) + 1];
        strncpy(p->key_name, key_name, strlen(key_name));
        p->key_name[strlen(key_name)] = '\0';

        p->count = 1;
        p->pre = tail->pre;
        p->next = tail;
        tail->pre->next = p;
        tail->pre = p;
    }
    return p->_id;
}

attribute* catalog::search(char* key_type, char* key_name) {
    attribute *cur = head->next;
    for (int i = 0; i < count; i++) {
        if (0 == strcmp(cur->key_type, key_type) &&
            0 == strcmp(cur->key_name, key_name)) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

my_vector<tuple*>& catalog::getarr() {
    return arr;
}

void catalog::print_tuple(tuple* t) {
    cout << "{";
    int size = t->key_num;
    int flag = 1;
    int curc = 0; //cur index for child
    for (int i = 0; i < size; i++) {
        attribute* att = search(t->aid[i]);
        // first attribute start without ' ';
        if (flag) flag = 0;
        else cout << ", ";
        cout << '"' << att->key_name << "\": ";
        int len = getLenFromOffset(t, i);
        if (!strcmp(att->key_type, "int")) {
            for (int j = 0; j < len; j++)
            cout << *(t->data.content() + t->offset[i] + j);
        } else if (!strcmp(att->key_type, "text")) {
            cout << '"';
            for (int j = 0; j < len; j++)
            cout << *(t->data.content() + t->offset[i] + j);
            cout << '"';
        } else if (!strcmp(att->key_type, "bool")) {
            if (*(t->data.content() + t->offset[i]) == 'T') {
                cout << "true";
            } else {
                cout << "false";
            }
        } else if (!strcmp(att->key_type, "nested_arr")) {
            cout << "[";
            if (len) cout << '"'; // don't cout without contents;
            for (int j = 0; j < len; j++) {
                if (*(t->data.content() + t->offset[i] + j) != delimeter) {
                    cout << *(t->data.content() + t->offset[i] + j);
                } else {
                    cout << "\", \"";
                }
            }
            if (len) cout << '"';
            cout << "]";
        } else if (!strcmp(att->key_type, "nested_obj")) {
            print_tuple(t->child[curc]);
            curc++;
        }
    }
    cout << "}";
    return;
}

attribute* catalog::search(int id) {
    attribute *cur = head->next;
    while (cur -> next != NULL) {
        if (cur -> _id == id) {
            return cur;
        }
        cur = cur -> next;
    }
    return NULL;
}

void my_swap(int &x,int &y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

int choose_pivot(int i,int j )
{
    return((i+j) /2);
}

void quicksort(my_vector<int> &v, int m, int n, my_vector<int> &od)
{
    int key,i,j,k;
    if( m < n)
    {
        k = choose_pivot(m,n);
        my_swap(v[m],v[k]);
        my_swap(od[m], od[k]);
        key = v[m];
        i = m+1;
        j = n;
        while(i <= j)
        {
            while((i <= n) && (v[i] <= key))
            i++;
            while((j >= m) && (v[j] > key))
            j--;
            if( i < j) {
                my_swap(v[i],v[j]);
                my_swap(od[i], od[j]);
            }
        }
        my_swap(v[m],v[j]);
        my_swap(od[m], od[j]);
        quicksort(v,m,j-1, od);
        quicksort(v,j+1,n, od);
    }
}

tuple* catalog::sort_id(tuple* t) {
    //sort according to aid
    my_vector<int> ori_order;
    int length = t->key_num;
    for (int i = 0; i < length; i++) ori_order.add(i);

    quicksort(t->aid, 0, t->aid.getSize()-1, ori_order);

    tuple* nt = new tuple;
    initial(nt);
    // creat aid
    nt->key_num = t->key_num;
    length = t->key_num;
    for (int i = 0; i < length; i++) {
        nt->aid.add(t->aid[i]);
    }
    // creat offset
    length = t->offset.getSize();
    int len = 0;
    for (int i = 0; i < length; i++) {
        nt->offset.add(len);
        len += getLenFromOffset(t, ori_order[i]);
    }
    //for debug if (t->len != len)
    nt->len = len;
    //creat data and child
    my_vector<int> Caid; //aid of child
    length = t->key_num;
    for (int i = 0; i < length; i++) {
        int len = getLenFromOffset(t, ori_order[i]);
        if (len == 0) {
            attribute* att = search(t->aid[ori_order[i]]);
            assert(att != NULL);
            if (!strcmp(att->key_type, "nested_obj")) {
                Caid.add(ori_order[i]);
                continue;
            }
        }
        char src[len+1];
        strncpy(src, t->data.content() + t->offset[ori_order[i]], len);
        src[len] = '\0';
        nt->data = nt->data + src;
    }
    //creat child
    nt->child_num = t->child_num;
    //if (child_num != Cod.getSize())
    my_vector<int> Cod;  // order of child
    length = nt->child_num;
    for (int i = 0; i < length; i++) Cod.add(i);
    quicksort(Caid, 0, length-1, Cod);
    for (int i = 0; i < length; i++) {
        tuple* nct = sort_id(t->child[Cod[i]]); // child will be release here
        nt->child.add(nct);
    }

    // don't release child, since children were release below
    if (t != NULL) {
        t->aid.vector_release();
        t->offset.vector_release();
        t->child.vector_release();
        delete t;
    }
    ori_order.vector_release();
    Cod.vector_release();
    Caid.vector_release();
    return nt;
}

char* catalog::search_id(int id) {
    // you can use cur_point to make it better
    attribute *cur = head->next;
    while (cur -> next != NULL) {
        if (cur -> _id == id) {
            return cur -> key_name;
        }
        cur = cur -> next;
    }
    return NULL;
}


void catalog::Find() {
    my_string key_name;
    char b[MAXN];
    cout << "input key_name"<<endl;
    cin >> key_name;
    cout << "input key_value"<<endl;
    getchar();
    gets(b);
    my_string key_value(b);
    if (key_value.content()[0] == '"') {
        int size = key_value.size();
        if (key_value.content()[size-1] != '"') {
            cout << "wrong input !!!" << endl;
            //continue;
        }
        char str[size - 1];
        for (int i = 0; i < size - 2; i++) {
            str[i] = key_value.content()[i+1];
        }
        str[size - 2] = '\0';
        find(key_name.content(), str);
    } else if (!strcmp(key_name.content(), "true")) {
        find(key_name.content(), true);
    } else if (!strcmp(key_name.content(), "false")) {
        find(key_name.content(), false);
    } else if (key_value.content()[0] >= '0' && key_value.content()[0] <= '9') {
        int num = 0;
        int size = key_value.size();
        for (int i = 0; i < size; i++) {
            num = num*10 + key_value.content()[i] - '0';
        }
        find(key_name.content(), num);
    } else if (key_value.content()[0] == '[') {
        int size = key_value.size();
        if (key_value.content()[size-1] != ']') {
            cout << "wrong input !!!" << endl;
            //continue;
        }
        my_vector<my_string> v;
        int i = 1, ok = 1;
        while (i < size) {
            if(key_value.content()[i] != '"') {
                cout << "wrong input !!!" << endl;
                ok = 0;
                break;
            }
            i++;//'"'
            char str2[size];
            int cur = 0;
            while (i < size && key_value.content()[i] != '"') {
                str2[cur] = key_value.content()[i];
                i++, cur++;
            }
            str2[cur] = '\0';
            if (i >= size) {
                cout << "wrong input !!!" << endl;
                ok = 0;
            } else {
                my_string str(str2);
                v.add(str);
                i++;//'"';
                if (key_value.content()[i] != ',' && i != size - 1) {
                    cout << "wrong input !!!" << endl;
                    cout << key_value.content()[i] <<endl;
                    break;
                }
                i++;//',' and ' ';
                i++;
            }
        }
        if (ok)
            find(key_name.content(), v);
        v.vector_release();
    } else {
        cout << "input error!!!"<<endl;
    }
}


//return index of id from left to right
int binary_search(my_vector<int>& aid, int low, int high, int goal) {
    int middle = (low + high)/2;
    while(low <= high)
    {
        middle = (low + high)/2;
        if(aid[middle] == goal)
        return middle;
        else if(aid[middle] > goal)
        high = middle - 1;
        else
        low = middle + 1;
    }
    return -1;
}

int catalog::find_int(tuple* t, const int id, const int& key_value, bool& is_find) {
    int num = 0;
    int ind = binary_search(t->aid, 0, t->aid.getSize() - 1, id);  //find index of aid.
    if (ind != -1) {
        int len = getLenFromOffset(t, ind);
        if (len) {
            int ans = 0;
            for(int j = 0; j < len; j++){
                ans = ans*10 + *(t->data.content() + t->offset[ind] + j) - '0';
            }
            if (ans == key_value) {
                is_find = true;
            }
        }
        num++;
    }
    int cnum = t->child_num;
    for (int j = 0; j < cnum; j++) {
        num += find_int(t->child[j], id, key_value, is_find);
    }
    return num;
}

void catalog::find(char* key_name, const int& key_value) {
    char type[10] = "int";
    attribute* att = search(type, key_name);
    if (att == NULL) {
        cout<< "NONE"<<endl;
        return;
    }
    int size = arr.getSize();
    int getnum = 0;
    int first = 1;
    bool is_ok = false;
    for (int i = 0; i < size; i++) {
        bool is_find = false;
        int del = find_int(arr[i], att->_id, key_value, is_find);
        getnum += del;
        if (is_find) {
            is_ok = true;
            if (first) first = 0;
            else cout << ",\n";
            print_tuple(arr[i]);
        }
        if (getnum >= att->count) break;
    }
    if (!is_ok) {
        cout<< "NONE";
    }
    cout << endl;
    return;
}

int catalog::find_char(tuple* t, const int id, const char* key_value, bool& is_find) {
    int num = 0;
    int ind = binary_search(t->aid, 0, t->aid.getSize() - 1, id);  //find index of aid.
    if (ind != -1) {
        int len = getLenFromOffset(t, ind);
        char str[len+1];
        strncpy(str, t->data.content() + t->offset[ind], len);
        str[len] = '\0';
        if (!strcmp(str, key_value)) {
            is_find = true;
        }
        num++;
    }
    int cnum = t->child_num;
    for (int j = 0; j < cnum; j++) {
        num += find_char(t->child[j], id, key_value, is_find);
    }
    return num;
}

void catalog::find(char* key_name, const char* key_value) {
    char type[10] = "text";
    attribute* att = search(type, key_name);
    if (att == NULL) {
        cout<< "NONE"<<endl;
        return;
    }
    int size = arr.getSize();
    int getnum = 0;
    int first = 1;
    bool is_ok = false;
    for (int i = 0; i < size; i++) {
        bool is_find = false;
        int del = find_char(arr[i], att->_id, key_value, is_find);
        getnum += del;
        if (is_find) {
            is_ok = true;
            if (first) first = 0;
            else cout << ",\n";
            print_tuple(arr[i]);
        }
        if (getnum >= att->count) break;
    }
    if (!is_ok) {
        cout<< "NONE";
    }
    cout << endl;
    return;
}

int catalog::find_bool(tuple* t, const int id, const bool& key_value, bool& is_find) {
    int num = 0;
    int ind = binary_search(t->aid, 0, t->aid.getSize() - 1, id);  //find index of aid.
    if (ind != -1) {
        int len = getLenFromOffset(t, ind);
        assert(len == 1);
        if (key_value) {
            if (*(t->data.content() + t->offset[ind]) == 'T') {
                is_find = true;
            }
        } else {
            if (*(t->data.content() + t->offset[ind]) == 'F') {
                is_find = true;
            }
        }
        num++;
    }
    int cnum = t->child_num;
    for (int j = 0; j < cnum; j++) {
        num += find_bool(t->child[j], id, key_value, is_find);
    }
    return num;
}

void catalog::find(char* key_name, const bool& key_value) {
    char type[10] = "bool";
    attribute* att = search(type, key_name);
    if (att == NULL) {
        cout<< "NONE"<<endl;
        return;
    }
    int size = arr.getSize();
    int getnum = 0;
    int first = 1;
    bool is_ok = false;
    for (int i = 0; i < size; i++) {
        bool is_find = false;
        int del = find_bool(arr[i], att->_id, key_value, is_find);
        getnum += del;
        if (is_find) {
            is_ok = true;
            if (first) first = 0;
            else cout << ",\n";
            print_tuple(arr[i]);
        }
        if (getnum >= att->count) break;
    }
    if (!is_ok) {
        cout<< "NONE";
    }
    cout << endl;
    return;
}

// cannot work well
int catalog::find_nested_arr(tuple* t, const int id, my_vector<my_string>& key_value, bool& is_find) {
    int num = 0;
    int ind = binary_search(t->aid, 0, t->aid.getSize() - 1, id);  //find index of aid.
    if (ind != -1) {
        int len = getLenFromOffset(t, ind);
        my_string str;
        int cur = 0;
        int size = key_value.getSize();
        if (len == 0 && size == 0) is_find = true;
        int i = 0;
        while (i < len && cur < size) {
            int ori = i;
            while (i < len && *(t->data.content() + t->offset[ind] + i) != delimeter) {
                i++;
            }
            int length = i - ori;
            if (key_value[cur].size() != length) break;
            char str[length+1];
            strncpy(str, t->data.content() + t->offset[ind] + ori, length);
            str[length] = '\0';
            if (strcmp(key_value[cur].content(), str)) break;
            cur++;
            if (*(t->data.content() + t->offset[ind] + i) == delimeter) i++;
        }
        if (i == len && cur == size) is_find = true;
        num++;
    }
    int cnum = t->child_num;
    for (int j = 0; j < cnum; j++) {
        num += find_nested_arr(t->child[j], id, key_value, is_find);
    }
    return num;
}

void catalog::find(char* key_name, my_vector<my_string>& key_value) {
    char type[20] = "nested_arr";
    attribute* att = search(type, key_name);
    if (att == NULL) {
        cout<< "NONE"<<endl;
        return;
    }
    int size = arr.getSize();
    int getnum = 0;
    int first = 1;
    bool is_ok = false;
    for (int i = 0; i < size; i++) {
        bool is_find = false;
        int del = find_nested_arr(arr[i], att->_id, key_value, is_find);
        getnum += del;
        if (is_find) {
            is_ok = true;
            if (first) first = 0;
            else cout << ",\n";
            print_tuple(arr[i]);
        }
        if (getnum >= att->count) break;
    }
    if (!is_ok) {
        cout<< "NONE";
    }
    cout << endl;
    return;
}

bool is_equal(tuple* a, tuple* b) {
    if (a->key_num != b->key_num || a->len != b->len || a->child_num != b->child_num) return false;
    for (int i = 0; i < a->key_num; i++) {
        if (a->aid[i] != b->aid[i]) return false;
        if (a->offset[i] != b->offset[i]) return false;
    }
    if (strcmp(a->data.content(), b->data.content())) return false;
    for (int i = 0; i < a->child_num; i++) {
        if (!is_equal(a->child[i], b->child[i])) return false;
    }
    return true;
}

int catalog::find_nested_obj(tuple* t, const int id, tuple& key_value, bool& is_find) {
    int num = 0;
    int ind = binary_search(t->aid, 0, t->aid.getSize() - 1, id);  //find index of aid.
    if (ind != -1) {
        int size = t->child_num;
        for (int i = 0; i < size; i++) {
            if (is_equal(t->child[i], &key_value)) is_find = true;
        }
        num++;
    }
    int cnum = t->child_num;
    for (int j = 0; j < cnum; j++) {
        num += find_nested_obj(t->child[j], id, key_value, is_find);
    }
    return num;
}

void catalog::find(char* key_name, tuple& key_value) {
    char type[20] = "nested_obj";
    attribute* att = search(type, key_name);
    if (att == NULL) {
        cout<< "NONE"<<endl;
        return;
    }
    int size = arr.getSize();
    int getnum = 0;
    int first = 1;
    bool is_ok = false;
    for (int i = 0; i < size; i++) {
        bool is_find = false;
        int del = find_nested_obj(arr[i], att->_id, key_value, is_find);
        getnum += del;
        if (is_find) {
            is_ok = true;
            if (first) first = 0;
            else cout << ",\n";
            print_tuple(arr[i]);
        }
        if (getnum >= att->count) break;
    }
    if (!is_ok) {
        cout<< "NONE";
    }
    cout << endl;
    return;
}
