#ifndef READ_H
#define READ_H

#include <cstdio>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include "my_string.h"
#include "serial.h"
#include "my_vector.cpp"

// read a string with a '\0' from fp;
my_string read_text(FILE* fp);
// read a integer from fp;
int read_int(FILE* fp);
// read a bool variable from fp;
bool read_bool(FILE* fp);
// read a nested_arr separated by delimeter from fp;
my_string read_nested_arr(FILE* fp);
// read a tuple from fp into t
tuple* read_tuple(FILE* fp);

#endif /* READ_H */
