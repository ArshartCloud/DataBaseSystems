#ifndef CHANGE_BACK_TO_JSON_H
#define CHANGE_BACK_TO_JSON_H

#include <iostream>
#include "serial.h"
#include "my_string.h"
#include "my_vector.cpp"
#include "catalog.h"
#include <cstdio>
#include <cstring>
using namespace std;

struct form {
    int count; // the total
    int cur;
    my_vector<char> data;
    my_vector<int> aid; // the number of aid
    my_vector<char*> name; // to save each aid's name
    my_vector<int> offset; // record the offsets
   // my_vector<char> str;
    //my_vactor<my_vector<char>> nest_arr;
};

class tran {
	public:
	void read_detail(FILE *in, catalog* CATALOG, form &json); // read the information from serial
        int add_num(FILE *in, form &json);
	void write(FILE *in, FILE *out, catalog* CATALOG, form &json);
        void get_aid(FILE *in, form &json);
        void get_offset(FILE *in, form &json);
        void get_data(FILE *in, form &json);
        void get_name(catalog * CATALOG, form &json);
        void write_arr(FILE *out, form json, int&k, int &z);
        void write_bool(FILE *out, form json, int &k);
        void write_text(FILE *out, form json, int&k, int &z);
};

//void print(FILE *in, FILE *out, catalog* CATALOG) {}


#endif
