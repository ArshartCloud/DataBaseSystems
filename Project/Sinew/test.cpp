#include <iostream>
#include <cstdio>
#include "write.h"
#include "catalog.h"
#include "print.h"
using namespace std;

int main(int argc, char *argv[]) {
    FILE* in;
    FILE* out;
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
    fclose(out);

    // Transform serial to json
    // in = fopen("output", "rb");
    // if (NULL == in) {
    //     cout << "output open failed" << endl;
    //     return 0;
    // }
    // out = fopen("input_.json", "w");
    // if (NULL == out) {
    //     cout << "input_.json open failed" << endl;
    //     return 0;
    // }

    // print(in, out, &CATALOG);
    // fclose(in);
    // fclose(out);

    return 0;
}

