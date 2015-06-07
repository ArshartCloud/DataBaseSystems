#include "serial.h"
#include <cstring>
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

void sort_id(tuple* t) {
    return;
}



