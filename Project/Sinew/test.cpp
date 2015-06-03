#include <iostream>
#include <cstdio>
#include <cassert>
#include "catalog.h"
#include "my_string.h"
//#define DEBUG
using namespace std;

int main(int argc, char *argv[]) {
    catalog log;
    FILE *fp;
    fp = fopen("input.json", "r");
    assert(fp != NULL);

    char ch;
//    fseek(fp, -1, SEEK_CUR);
//    char* str = read_string(fp);

    int k = 25;
    // extra data
    while (k--) {
        ch = fgetc(fp);
        if ('"' == ch) {
            read_text(fp);
        } else if (ch >= '0' && ch <= '9') {
            read_int(fp);
        } else if ('f' == ch || 't' == ch) {
            read_bool(fp);
        } else if ('[' == ch) {
            read_nested_arr(fp);
        } else if ('{' == ch) {
            read_nested_obj(fp);
        }
    }

    fclose(fp);
    return 0;
}

