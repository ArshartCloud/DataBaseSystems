#include "my_string.h"
#define DEBUG
using namespace std;

const char delimeter = ' ';

char* read_text(FILE* fp) {
    int count = 0;
    char ch;
    while ((ch = fgetc(fp)) != '"') {
        ++count;
    }
    fseek(fp, -(count + 1), SEEK_CUR);
    char* str = new char[count + 1];
    fread(str, count, 1, fp);
    ch = fgetc(fp);
    str[count] = '\0';
#ifdef DEBUG
    cout << "Read a text" << endl;
    cout << "length = " << strlen(str) << endl;
    cout << "str = " << str << endl;
    cout << endl;
#endif // DEBUG
    return str;
}

int read_int(FILE* fp) {
    int k = 0;
    char ch;
    fseek(fp, -1, SEEK_CUR);
    while ((ch = fgetc(fp)) >= '0' && (ch <= '9')) {
        k = k * 10 + (ch - '0');
    }
#ifdef DEBUG
    cout << "Read a integer" << endl;
    cout << "int = " << k << endl;
    cout << endl;
#endif
    return k;
}

bool read_bool(FILE* fp) {
    bool k;
    char ch;
    int skip;
    fseek(fp, -1, SEEK_CUR);
    ch = fgetc(fp);
    assert('f' == ch || 't' == ch);
    if ('f' == ch) {
        k = false;
        skip = 4;
    } else if ('t' == ch) {
        k = true;
        skip = 3;
    }
    for (int i = 0; i < skip; i++) {
        ch = fgetc(fp);
    }
#ifdef DEBUG
    cout << "Read a bool variable" << endl;
    cout << "bool = " << boolalpha << k << endl;
    cout << endl;
#endif // DEBUG
    return k;
}

char* read_nested_arr(FILE* fp) {

}

void read_nested_obj(FILE *fp) {

}
