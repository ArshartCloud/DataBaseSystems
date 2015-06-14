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

int main(int argc, char *argv[]) {
    FILE* in;
    FILE* out;
    in = fopen("input.json", "r"); 
    if (NULL == in) {
        cout << "onput open failed" << endl; 
        return 0;
    }
    out = fopen("output1", "wb");
    if (NULL == out) {
        cout << "in.json open failed" << endl;
        return 0;
    }
    catalog CATALOG;
    write_file(in, out, &CATALOG);
   // CATALOG.print();
    fclose(in);
    fclose(out);
    in = fopen("output1", "rb");
    out = fopen("in.json", "w");
    print(in, out, &CATALOG);
   // CATALOG.print();
    fclose(in);
    fclose(out);


    ifstream input, output;
    input.open("in.json");
    output.open("input.json");
    while (!input.eof()) {
      string s1 = "", s2 = "";
      getline(input, s1);
      getline(output, s2);
      if (s1 != s2) {
         cout << "error!\n";
         cout << s1 << endl << endl << s2 << endl;
         input.close();
         output.close();
         return 0;
      }
    }
    input.close();
    output.close();
    cout << "done!\n";
    return 0;

}

