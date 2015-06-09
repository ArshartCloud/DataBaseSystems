#include <iostream>
#include <cstdio>
#include "write.h"
#include "catalog.h"

using namespace std;

int main(int argc, char *argv[]) {
    FILE* in;
    FILE* out;
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
    CATALOG.print();

    fclose(in);
    fclose(out);
    return 0;
}

