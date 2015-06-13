#ifndef SERIAL_H
#define SERIAL_H

#include <cstdio>
#include <iostream>
#include <cstring>
#include "my_vector.cpp"
#include "my_string.h"

struct tuple {
    int key_num;
    my_vector<int> aid;
    my_vector<int> offset;
    // length of all data, except for nested_obj
    int len;
    // key data except nested _obj
    my_string data;
    my_vector<tuple*> child;
    // number of nested_obj
    int child_num;
};

// initialize a tuple
void initial(tuple* t);
// add a integer key into a tuple
void add_int(tuple* t, int id, my_string key_value);
// add a text/nested_arr key into a tuple
void add_text(tuple* t, int id, my_string key_value);
// add a bool variable key into a tuple
void add_bool(tuple* t, int id, bool key_value);
// add a nested_arr key into a tuple
void add_nested_arr(tuple *t, int id, my_string key_value);
// add a nested_obj key into a tuple
void add_nested_obj(tuple* t, int id, tuple* nested);
// release memory of a tuple
void tuple_release(tuple* t);
// sort the key with aid using binary search
tuple* sort_id(tuple* t);

#endif /* SERIAL_H */
