#include "catalog.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

const int padding = 20;

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

void catalog::find(char* key_name, void* key_value) {
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

char* catalog::search_id(int id) {
   // you can use cur_point to make it better
    attribute *cur = head->next;
    while (cur -> next != NULL) {
        if (cur -> _id == id) {
//	cout << cur -> key_name << endl;
		return cur -> key_name;
	}
      //  cout << count << endl; 
        cur = cur -> next;
    }
    cout << "not find id!\n";
    return NULL;
}
