#include <iostream>
#include <cstdio>
#include "write.h"
#include "catalog.h"
#include "change_back_to_json.h"
#include "my_string.h"
#include "my_vector.cpp"
#include <string>
#include "print.h"
#include <fstream>

using namespace std;
void print(FILE *in, FILE *out, catalog* CATALOG) {
    fprintf(out, "[\n");
    char ch;
    ch = fgetc(in);
    ch = fgetc(in);
    while(ch != ']') {
      form j2;
      while(1) {
        ch = fgetc(in);
        if (ch == EOF || ch == '\n') break;
        else j2.str.add(ch);
      }
      tran a;
      if (j2.str.getSize() > 10) {
        a.write(in, out, CATALOG, j2);
      }
     j2.data.vector_release();
     j2.aid.vector_release();
        //int size = name.getSize();
        //for (int i = 0; i < size; i++) name[i] = NULL;
     j2.name.vector_release();
     j2.offset.vector_release();
     j2.str.vector_release();
     ch = fgetc(in);
     if (ch != ']') fprintf(out, ",\n");
     else fprintf(out, "\n");
   }
   fprintf(out, "]\n");
}

