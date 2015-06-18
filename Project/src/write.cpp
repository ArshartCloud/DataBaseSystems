#include <cstdio>
#include <iostream>
#include "read.h"
#include "write.h"
#include "serial.h"
#include "my_vector.cpp"
#include <cstring>

void write_tuple(FILE* fp, tuple* t) {
    page_w Write;
//    fprintf(fp, "{count: %d", t->key_num);
    char s1[] = "{count: ";
    Write.my_fwrite(s1, strlen(s1), 1, fp);
    Write.my_fwrite(&t->key_num, sizeof(t->key_num), 1, fp);
    char s2[] = ", aid", s3[] = ": ";
    for (int i = 0; i < t->key_num; i++) {
//        fprintf(fp, ", aid%d: %d", i, t->aid[i]);
        Write.my_fwrite(s2, strlen(s2), 1, fp);
        Write.my_fwrite(&i, sizeof(i), 1, fp);
        Write.my_fwrite(s3, strlen(s3), 1, fp);
        Write.my_fwrite(&t->aid[i], sizeof(t->aid[i]), 1, fp);
    }
    char s4[] = ", offset";
    for (int i = 0; i < t->key_num; i++) {
//        fprintf(fp, ", offset%d: %d", i, t->offset[i]);
        Write.my_fwrite(s4, strlen(s4), 1, fp);
        Write.my_fwrite(&i, sizeof(i), 1, fp);
        Write.my_fwrite(s3, strlen(s3), 1, fp);
        Write.my_fwrite(&t->offset[i], sizeof(t->offset[i]), 1, fp);
    }
//    fprintf(fp, ", len: %d, data: %s}", t->len, t->data.content());
    char s5[] = ", len: ", s6[] = ", data: ", s7 = '}';
    Write.my_fwrite(s5, strlen(s5), 1, fp);
    Write.my_fwrite(&t->len, sizeof(t->len), 1, fp);
    Write.my_fwrite(s6, strlen(s6), 1, fp);
    Write.my_fwrite(t->data.content(), strlen(t->data.content()), 1, fp);
    Write.my_fwrite(&s7, sizeof(s7), 1, fp);

    char s8[] = ", ";
    for (int i = 0; i < t->child_num; i++) {
//        fprintf(fp, ", ");
        Write.my_fwrite(s8, strlen(s8), 1, fp);
        write_tuple(fp, (t->child[i]));
    }
    return;
}

void write_file(FILE* in, FILE* out,catalog* CATALOG) {
//    fprintf(out, "[\n");
    page_r Read;
    page_w Write;

    char s1[] = "[\n";
    Write.my_fwrite(s1, strlen(s1), 1, out);
    tuple *t;
    char ch;
     // left square bracket, [
    ch = Read.my_fgetc(in);
    // endline, \n
    ch = Read.my_fgetc(in);

    while (1) {
        // left curly bracket or right square bracket, { , ]
        ch = Read.my_fgetc(in);
        if (']' == ch) {
            break;
        }
        t = read_tuple(in, CATALOG);
        write_tuple(out, t);
//        fprintf(out, ",\n");
        char s2[] = ",\n";
        Write.my_fwrite(s2, strlen(s2), 1, out);
        CATALOG->getarr().add(t);
        // colon, ,
        ch = Read.my_fgetc(in);
        // endline, \n
        ch = Read.my_fgetc(in);
        if (']' == ch) {
            break;
        }
    }
//    fprintf(out, "]\n");
    char s3[] = "]\n";
    Write.my_fwrite(s3, strlen(s3), 1, out);
    return;
}
