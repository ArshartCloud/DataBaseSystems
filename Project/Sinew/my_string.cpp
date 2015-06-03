#include "my_string.h"
#define DEBUG
using namespace std;

const char delimeter = '-';

// return a string with a delimeter
char* read_text(FILE* fp) {
    int count = 0;
    char ch;
    while ((ch = fgetc(fp)) != '"') {
        ++count;
    }
    fseek(fp, -(count + 1), SEEK_CUR);
    char *str = (char*)malloc(sizeof(count + 1));
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
    int count = 0;
    char ch;
    char *s = NULL;
    char *s_next;
    while ((ch = fgetc(fp)) != ']') {
        if ('"' == ch) {
            s_next = read_text(fp);
            if (s != NULL) {
                join(s, s_next);
            } else {
                s = (char*)malloc(sizeof(strlen(s_next)));
                strncpy(s, s_next, sizeof(s));
            }
        }
    }
#ifdef DEBUG
    cout << "Read a nested_arr" << endl;
    cout << s << endl;
    cout << endl;
#endif // MACRO
    return s;
}


void read_tuple(FILE *fp, tuple* t) {

}

void join(char* s, char* s_next) {
    int length = strlen(s);
    cout << "join " << s << " and " << s_next << endl;
    s = (char*)realloc(s, strlen(s) + strlen(s_next) + 1);
    s[length] = delimeter;
    strncpy(s + length + 1, s_next, sizeof(s));

}
