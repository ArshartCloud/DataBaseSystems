#include "my_string.h"

#define DEBUG
using namespace std;

const char delimeter = '-';

// return a string with a delimeter '/0'
char* read_text(FILE* fp) {
    int count = 0;
    char ch;
    while ((ch = fgetc(fp)) != '"') {
        ++count;
    }
    fseek(fp, -(count + 1), SEEK_CUR);
    char *str = (char*)malloc(sizeof(count + 1));
    fread(str, count, 1, fp);
    ch = fgetc(fp); // "
    str[count] = '\0';
#ifdef DEBUG
    cout << "Read a text" << endl;
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
            // if (s != NULL) {
            //     join_str(s, s_next, strlen(s_next));
            // } else {
            //     s = (char*)malloc((strlen(s_next)));
            //     strncpy(s, s_next, sizeof(s));
            // }
            join_str(s, s_next, strlen(s_next));
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

void join_str(char* s, char* s_next, int count) {
    if (NULL == s) {
        s = (char*)malloc(count + 1);
        strncpy(s, s_next, count);
        s[count] = '/0';
    } else {
        int length = strlen(s);
        s = (char*)realloc(s, length + count + 1);
        strncpy(s + length, s_next, count);
        s[length + count] = '/0';
    }
}

void join_int(int* k, int num, int ele) {
    if (NULL == k) {
        k = (int*)malloc(sizeof(int));
    } else {
        k = (int*)realloc(k, sizeof(int) * (num + 1));
        k += num;
    }
    *k = ele;
}


