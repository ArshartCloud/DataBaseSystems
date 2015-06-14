#include "write.h"
#include <cstdio>
#include <iostream>
#include "read.h"
#include "serial.h"
#include "my_vector.cpp"

void write_tuple(FILE* fp, tuple* t) {
    fprintf(fp, "{count: %d", t->key_num);
    for (int i = 0; i < t->key_num; i++) {
        fprintf(fp, ", aid%d: %d", i, t->aid[i]);
    }
    for (int i = 0; i < t->key_num; i++) {
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
//    my_vector<tuple*> &arr = (CATALOG->getarr());
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
        CATALOG->getarr().add(t);
        // colon, ,
        ch = fgetc(in);
        // endline, \n
        ch = fgetc(in);
        if (']' == ch) {
            break;
        }
    }
    fprintf(out, "]\n");
    return;
}
