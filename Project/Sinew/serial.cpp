#include "serial.h"
using namespace std;

void initial(tuple* t) {
    t->key_num = 0;
    t->len = 0;
    t->data = "";
    t->child_num = 0;
    return;
}

void add_int(tuple* t, int id, my_string key_value) {
    add_text(t, id, key_value);
    return;
}

void add_text(tuple* t, int id, my_string key_value) {
    ++t->key_num;
    t->aid.add(id);
    t->offset.add(t->len);
    t->data = t->data + key_value;
    t->len += key_value.size();
    return;
}

void add_bool(tuple* t, int id, bool key_value) {
    ++t->key_num;
    t->aid.add(id);
    t->offset.add(t->len);
    t->len += 1;
    my_string s;
    if (true == key_value) {
        s = "T";
    } else {
        s = "F";
    }
    t->data = t->data + s;
    return;
}

void add_nested_arr(tuple *t, int id, my_string key_value) {
    add_text(t, id, key_value);
    return;
}

void add_nested_obj(tuple* t, int id, tuple* nested) {
    ++t->key_num;
    t->aid.add(id);
    t->offset.add(t->len);
    t->len += 0;
    t->child.add(nested);
    ++t->child_num;
    return;
}

void tuple_release(tuple* t) {
     for (int i = 0; i < t->child_num; i++) {
         tuple_release(t->child[i]);
     }
    if (t != NULL) {
        t->aid.vector_release();
        t->offset.vector_release();
        t->child.vector_release();
        delete t;
    }
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

int getLenFromOffset(tuple* t, int offid) {
  if (offid != t->key_num - 1)
    return (t->offset[offid+1] - t->offset[offid]);
  else
    return (t->len - t->offset[offid]);
}

tuple* sort_id(tuple* t) {
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
        Caid.add(ori_order[i]);
        continue;
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
