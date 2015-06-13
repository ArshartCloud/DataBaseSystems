#include "my_string.h"
#include <cassert>

my_string::my_string(int count) {
    str = new char[count + 1];
    str[count] = '\0';
    length = 0;
}

my_string::my_string(const char* src) {
    if (NULL != src) {
        int len = strlen(src);
        str = new char[len + 1];
        strncpy(str, src, len);
        str[len] = '\0';
        length = len;
    } else {
        str = new char[1];
        str[0] = '\0';
        length = 0;
    }
}

my_string::my_string(my_string& src) {
    str = new char[src.length + 1];
    strncpy(str, src.str, src.length);
    str[src.length] = '\0';
    length = src.length;
}

my_string::~my_string() {
    delete[] str;
}

my_string& my_string::operator=(const my_string& src) {
    if (this != &src) {
        delete[] str;
        str = new char[src.length + 1];
        strncpy(str, src.str, src.length);
        str[src.length] = '\0';
        length = src.length;
    }
    return *this;
}

my_string& my_string::operator=(const char* src) {
    if (NULL != src) {
        delete[] str;
        length = strlen(src);
        str = new char[length + 1];
        strncpy(str, src, length);
        str[length] = '\0';
    }
    return *this;
}

my_string my_string::operator+(const my_string& src) {
    my_string newStr;
    char* p = newStr.content();
    delete[] p;
    newStr.length = this->length + src.length;
    newStr.str = new char[this->length + src.length + 1];
    strncpy(newStr.str, this->str, this->length);
    strncpy(newStr.str + this->length, src.str, src.length);
    newStr.str[this->length + src.length] = '\0';
    return newStr;
}

my_string my_string::operator+(const char* src) {
    my_string newStr;
    char* p = newStr.content();
    delete[] p;
    assert(src != NULL);

    newStr.length = this->length + strlen(src);
    newStr.str = new char[this->length + strlen(src) + 1];
    strncpy(newStr.str, this->str, this->length);
    strncpy(newStr.str + this->length, src, (strlen(src)));
    newStr.str[this->length + strlen(src)] = '\0';
    return newStr;
}

char* my_string::content(void) {
    return str;
}

int my_string::size(void) {
    return this->length;
}

ostream& operator<<(ostream& os, my_string& s) {
    os << s.str;
    return os;
}

istream& operator>>(istream& is, my_string& s) {
    is >> s.str;
    return is;
}
