#ifndef SERIALIZER_H
#define SERIALIZER_H

struct tuple {
    int key_num;
    int *aid; //  n elements
    int *offset;  // (n - 1) elements
    int len; // length of all data
    char *data;
    tuple *child;  // nested_obj
    int child_num;  // number of nested_obj
};

void initial(tuple* t);
void add_int(tuple* t, int id, int key_value);
void add_text(tuple* t, int id, char* key_value);
void add_bool(tuple* t, int id, bool key_value);
void add_nested_obj(tuple* t, int id, FILE* fp);

// sort the key with aid using binary search
void sort_id(tuple* t);

#endif
