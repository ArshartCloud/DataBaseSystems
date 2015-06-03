#include "serializer.h"
#include <cassert>
#include "my_string.h"


void initial(tuple* t) {
    assert(t != NULL);

    t->key_num = 0;
    t->aid = NULL;
    t->offset = NULL;
    t->len = 0;
    t->data = NULL;
    t->child = NULL;
    t->child_num = 0
}

void add_int(tuple* t, int id, int key_value) {
    assert(t != NULL);

    join_int(t->aid, t->key_num, id);
    join_int(t->offset, t->key_num, sizeof(int));

    int* pos = (int*)(data + len);
    *pos = key_value;

    t->len += sizeof(int);
    ++t->key_num;
}

void add_text(tuple* t, int id, char* key_value) {
    assert(t != NULL);

    join_int(t->aid, t->key_num, id);
    join_int(t->offset, t->key_num, sizeof(int));

    join_str(t->data, key_value, strlen(key_value));

    t->len += strlen(key_value);
    ++t->key_num;
}

void add_bool(tuple* t, int id, bool key_value) {
    assert(t != NULL);

    join_int(t->aid, t->key_num, id);
    join_int(t->offset, t->key_num, sizeof(int));

    char* p = (char*)(&key_value);
    join_str(t->data, p, sizeof(bool));

    len += sizeof(bool);
    ++t->key_num;
}

void add_nested_obj(tuple* t, int id, FILE* fp) {
    assert(t != NULL);

    join_int(t->aid, t->key_num, id);
    join_int(t->offset, t->key_num, id);

    if (NULL == t->child) {
        t->child = (tuple*)malloc(sizeof(tuple));
    } else {
        t->child = (tuple*)realloc(t->child, sizeof(tuple) * (child_num + 1));
    }

    read_tuple(fp, t->(child + child_num));
    ++child_num;
    ++t->key_num;
}

void sort_id(tuple* t) {

}
