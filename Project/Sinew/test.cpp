#include <iostream>
#include <cstdio>
#include "write.h"
#include "catalog.h"
#include "print.h"
using namespace std;

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

    return 0;
}

