#include "catalog.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;
const int padding = 20;

catalog::catalog(void) {
    head = (attribute*)malloc(sizeof(attribute));
    tail = (attribute*)malloc(sizeof(attribute));
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
        tail->pre = tail->pre->pre;
        free (last->key_name);
        free (last->key_type);
        free (last);
    }
    free (head);
    free (tail);
}

void catalog::print(void) {
    // heading
    cout << setfill(' ') << left
         << setw(padding) << "_id"
         << setw(padding) << "Key_name"
         << setw(padding) << "Key_type"
         << setw(padding) << "count"
         << endl;
    // record
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

void catalog::insert_tuple(char* key_type, char* key_name) {
    attribute *p = search(key_type, key_name);
    if (p != NULL) {
        ++p->count;
    } else {
        p = (attribute*)malloc(sizeof(attribute));
        p->_id = ++count;
        strcpy(p->key_type, key_type);
        strcpy(p->key_name, key_name);
        p->count = 1;
        p->pre = tail->pre;
        p->next = tail;
        tail->pre->next = p;
        tail->pre = p;
    }
    return;
}

attribute* catalog::search(char* key_type, char* key_name) {
    attribute *cur = head->next;
    for (int i = 0; i < count; i++) {
        if (!strcmp(key_name, cur->key_name) && !strcmp(key_type, cur->key_type)) {
            return cur;
        }
    }
    return NULL;
}
