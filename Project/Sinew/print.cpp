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
      tran a;
      a.write(in, out, CATALOG, j2);
     j2.data.vector_release();
cout << "data clean\n";
     j2.aid.vector_release();
cout << "aid clean\n";
     j2.name.vector_release();
cout << "name clean\n";
     j2.offset.vector_release();
cout << "offset clean\n";
     ch = fgetc(in);
     if (ch != ']') fprintf(out, ",\n");
     else fprintf(out, "\n");
   }
   fprintf(out, "]\n");
}

