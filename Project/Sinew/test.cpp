#include <iostream>
#include <cstdio>
#include "write.h"
#include "catalog.h"
#include "print.h"
using namespace std;

#define DEBUG

void test_find(catalog& c) {
  while(1){
    my_string key_type, key_name;
    cout << "input key_type"<<endl;
    cin >> key_type;
    cout << "input key_name"<<endl;
    cin >> key_name;
    cout << "input key_value"<<endl;
    if (!strcmp(key_type.content(), "int")) {
      int key_value;
      cin >> key_value;
      c.find(key_name.content(), key_value);
    } else if (!strcmp(key_type.content(), "text")) {
      my_string key_value;
      cin >> key_value;
      c.find(key_name.content(), key_value.content());
    } else if (!strcmp(key_type.content(), "nested_arr")) {
      cout << "input strings, end with '|'"<<endl;
      my_vector<my_string> v;
      while (1) {
        my_string a;
        cin >> a;
        if (!strcmp(a.content(), "|")) break;
        v.add(a);
      }
//      my_string a("fairly");
 //     v.add(a);
      c.find(key_name.content(), v);
      v.vector_release();
    } else if (!strcmp(key_type.content(), "bool")) {
      bool key_value;
      cin >> key_value;
      c.find(key_name.content(), key_value);
    } else if (!strcmp(key_type.content(), "nested_obj")) {
      cout << "it is too difficult to test!";
    } else break;
  }
}


int main(int argc, char *argv[]) {
    FILE* in;
    FILE* out;
    page_r Read;
    page_w Write;
    // Transform json to serial
    in = fopen("input.json", "r");
    if (NULL == in) {
        cout << "input.json open failed" << endl;
        return 0;
    }
    out = fopen("output", "wb");
    if (NULL == out) {
        cout << "output open failed" << endl;
        return 0;
    }

    catalog CATALOG;
    write_file(in, out, &CATALOG);
    fclose(in);
    Write.flush(out);
    fclose(out);
    Read.reset();
    Write.reset();



    // Transform serial to json
    in = fopen("output", "rb");
    if (NULL == in) {
        cout << "output open failed" << endl;
        return 0;
    }
    out = fopen("input_.json", "w");
    if (NULL == out) {
        cout << "in.json open failed" << endl;
        return 0;
    }

    print(in, out, &CATALOG);
    fclose(in);
    Write.flush(out);
    fclose(out);

#ifdef DEBUG
test_find(CATALOG);
#endif

    return 0;
}

