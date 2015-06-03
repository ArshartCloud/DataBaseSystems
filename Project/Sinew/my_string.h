#ifndef MY_STRING_H
#define MY_STRING_H

#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>

// read a string from fp;
char* read_text(FILE* fp);
// read a integer from fp;
int read_int(FILE* fp);
// read a bool variable from fp;
bool read_bool(FILE* fp);
// read a nested_arr from fp;
char* read_nested_arr(FILE* fp);
// read a tuple into t
void read_tuple(FILE* fp, tuple* t);
// manual dynamic array
void join(char* s, char* s_next);
#endif /* MY_STRING_H */
