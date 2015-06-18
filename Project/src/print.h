#ifndef PRINT_H
#define PRINT_H
#include <cstdio>
#include "write.h"
#include "change_back_to_json.h"
#include <fstream>
#include "page_rw.h"

void print(FILE *in, FILE *out, catalog* CATALOG);

#endif
