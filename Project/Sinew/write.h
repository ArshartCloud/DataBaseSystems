#ifndef WRITE_H
#define WRITE_H

#include <cstdio>
#include <iostream>
#include "read.h"
#include "serial.h"
#include "my_vector.cpp"
using namespace std;

void write_tuple(FILE* fp, tuple* t);
void write_file(FILE* in, FILE* out,catalog* CATALOG);

void write_tuple(FILE* fp, tuple* t) {
    fprintf(fp, "{count: %d", t->key_num);
    for (int i = 0; i < t->key_num; i++) {
        fprintf(fp, ", aid%d: %d", i, t->aid[i]);
    }
    for (int i = 0; i < t->key_num - 1; i++) {
        fprintf(fp, ", offset%d: %d", i, t->offset[i]);
    }
    fprintf(fp, ", len: %d, data: %s}", t->len, t->data.content());
    for (int i = 0; i < t->child_num; i++) {
        fprintf(fp, ", ");
        write_tuple(fp, (t->child[i]));
    }
    return;
}

void write_file(FILE* in, FILE* out,catalog* CATALOG) {
    fprintf(out, "[\n");
    char ch;
    tuple *t;
    my_vector<tuple*> arr;
     // left square bracket, [
    ch = fgetc(in);
    // endline, \n
    ch = fgetc(in);

    while (1) {
        // left curly bracket or right square bracket, { , ]
        ch = fgetc(in);
        if (']' == ch) {
            break;
        }
        t = read_tuple(in, CATALOG);
        write_tuple(out, t);
        fprintf(out, ",\n");
        arr.add(t);
        // colon, ,
        ch = fgetc(in);
        // endline, \n
        ch = fgetc(in);
    }
    fprintf(out, "]\n");
    //  release memory
    int size = arr.getSize();
    for (int i = 0; i < size; i++) {
        tuple_release((arr[i]));
    }
    arr.vector_release();
    return;
}

#endif /* WRITE_H */
