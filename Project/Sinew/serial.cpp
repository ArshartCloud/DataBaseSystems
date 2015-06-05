#include "serial.h"
#include <cstring>

void initial(tuple* t) {
    assert(t != NULL);
    t->key_num = 0;
    t->len = 0;
    t->data = "";
    t->child_num = 0;
    return;
}

void add_int(tuple* t, int id, int key_value) {
    assert(t != NULL);
    int size = sizeof(int);

    ++t->key_num;
    t->aid.add(id);
    t->offset.add(t->len);
    t->len += size;
    // tranform a integer into string
    char *s = new char[size + 1];
    s[size] = '\0';
    strncpy(s, (char*)&id, size);
    t->data = t->data + s;

    delete[] s;
    return;
}

void add_text(tuple* t, int id, my_string key_value) {
    assert(t != NULL);

    ++t->key_num;
    t->aid.add(id);
    t->offset.add(t->len);
    t->len += key_value.size();
    t->data = t->data + key_value;
    return;
}

void add_bool(tuple* t, int id, bool key_value) {
    assert(t != NULL);
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
    tuple child;
    ++t->key_num;
    t->aid.add(id);
    t->offset.add(t->len);
    t->len += 0;
//    t->child.add(child);
    ++t->child_num;
    return;
}

void sort_id(tuple* t) {
    return;
}

void foo(tuple *t, int id, tuple* k) {

    return;
}
