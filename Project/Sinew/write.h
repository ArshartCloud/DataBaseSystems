#include <cstdio>
#include <iostream>
#include "read.h"

using namespace std;

void write_tuple(FILE* fp, tuple* t) {
    fputc('{', fp);
    fprintf(fp, "count: %d", t->key_num);
    for (int i = 0; i < t->key_num; i++) {
        fprintf(fp, ", aid%d: %d", i, t->aid[i]);
    }
    for (int i = 0; i < t->key_num - 1; i++) {
        fprintf(fp, ", offset%d: %d", i, t->offset[i]);
    }

    fprintf(fp, ", len: %d, data: %s", t->len, t->data.content());


    fputc('}', fp);

    for (int i = 0; i < t->child_num; i++) {
        fprintf(fp, ", ");
        write_tuple(fp, &(t->child[i]));
    }
    return;
}

void write_file(FILE* in, FILE* out,catalog* CATALOG) {
    fprintf(out, "[\n");
    char ch;
    tuple *t;
    ch = fgetc(in); // [
    ch = fgetc(in); // /n
//    ch = fgetc(in); // {
    while (1) {
        ch = fgetc(in); // left curly bracket
        t = read_tuple(in, CATALOG);
        write_tuple(out, t);
        tuple* c = &(t->child[0]);

        ch = fgetc(in); // colon or endline
        ch = fgetc(in); // endline or right square bracket

        if (']' == ch) {
            fputc('\n', out);
            break;
        } else {
            fputc(',', out);
            fputc('\n', out);
        }
    }
    fprintf(out, "]\n");
}
