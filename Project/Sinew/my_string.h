#ifndef MY_STRING_H
#define MY_STRING_H

#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>

// read a string from fp,
char* read_text(FILE* fp);
int read_int(FILE* fp);
bool read_bool(FILE* fp);
char* read_nested_arr(FILE* fp);
void read_nested_obj(FILE* fp);
#endif /* MY_STRING_H */
