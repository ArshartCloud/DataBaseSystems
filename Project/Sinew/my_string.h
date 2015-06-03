#ifndef MY_STRING_H
#define MY_STRING_H

#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include "serializer.h"

// read a string with a '\0' from fp;
char* read_text(FILE* fp);
// read a integer from fp;
int read_int(FILE* fp);
// read a bool variable from fp;
bool read_bool(FILE* fp);
// read a nested_arr separated by delimeter from fp;
char* read_nested_arr(FILE* fp);
// read a tuple from fp into t
void read_tuple(FILE* fp, tuple* t);
// append characters from s_next to the end of s with a '\0'
void join_str(char* s, char* s_next, int count);
// append a integer at the end of an array k
void join_int(int* k, int num, int ele);

#endif /* MY_STRING_H */
