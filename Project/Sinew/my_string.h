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

    bool operator==(const my_string& src);
    bool operator==(const char* src);

    int size();
private:
    // end with a '\0'
    char* str;
    int length;
};

#endif /* MY_STRING_H */