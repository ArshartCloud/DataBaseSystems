#ifndef WRITE_H
#define WRITE_H

#include <cstdio>
#include <iostream>
#include "read.h"
#include "serial.h"
#include "my_vector.cpp"
#include "page_rw.h"
using namespace std;

// in as json input, out as serial output, indexed by CATALOG
void write_file(FILE* in, FILE* out,catalog* CATALOG);
void write_tuple(FILE* fp, tuple* t);

#endif /* WRITE_H */
