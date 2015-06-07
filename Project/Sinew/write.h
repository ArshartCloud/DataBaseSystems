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


#endif /* WRITE_H */
