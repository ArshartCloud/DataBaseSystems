#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>
#include <cstring>
using namespace std;

// a simplified implementation of string
class my_string {
    friend ostream& operator<<(ostream& os, my_string& str);
    friend istream& operator>>(istream& os, my_string& str);
public:
    my_string(int count = 0);
    my_string(const char* src);
    my_string(my_string& src);
    ~my_string();
    my_string& operator=(const my_string& src);
    my_string operator+(const my_string& src);
    my_string& operator=(const char* src);
    my_string operator+(const char* src);
    // return a pointer to the string
    char* content(void);
    // return the length of the string
    int size(void);
private:
    // end with a '\0'
    char* str;
    int length;
};

#endif /* MY_STRING_H */
