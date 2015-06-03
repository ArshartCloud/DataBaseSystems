#include "catalog.h"
#include <iostream>
#include <cstdio>
#include <cassert>

using namespace std;

int read_string(FILE* p) {
    int count = 0;
    FILE* fp = p;
    char ch;
    while ((ch = fgetc(fp)) != '"') {
        cout << ch;
        ++count;
    }
    cout << endl;
    return count;
}


int main(int argc, char *argv[]) {
    catalog log;
    FILE *fp;
    fp = fopen("input.json", "r");
    assert(fp != NULL);


    char a;
    a = fgetc(fp);  // [
    a = fgetc(fp);  // /n
    a = fgetc(fp); // {
    a = fgetc(fp); // "
    int count;
//    fseek(fp, -1, SEEK_CUR);
    count = read_string(fp);
    cout << count << endl;
    a = fgetc(fp);
    a = fgetc(fp);
    a = fgetc(fp);
    a = fgetc(fp);
    a = fgetc(fp);
    cout << a << endl;



    fclose(fp);
    return 0;
}
