#ifndef SERIALIZER_H
#define SERIALIZER_H

struct tuple {
    int key_num;
    int *aid; //  n elements
    int *offset;  // (n - 1) elements
    int len;
    char *data;
    tuple *child;  // nested_obj
    int child_CNT;  // number of nested_obj
    tuple() {
        key_num = 0;
    }
};

// sort the key with aid using binary search
void sort_id(tuple* t);

void add_int(tuple* t, int id, int key_value);
void add_text(tuple* t, int id, char* key_value);
void add_bool(tuple* t, int id, bool key_value);
void add_nested_arr(tuple* t, int id, char* key_value);
void add_nested_obj(tuple* t, int id, tuple* child);


#endif
