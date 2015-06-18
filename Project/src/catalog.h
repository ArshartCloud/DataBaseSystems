#ifndef CATALOG_H
#define CATALOG_H
#include "my_vector.cpp"
#include "my_string.h"
#include "serial.h"

struct attribute {
    int _id;
    char* key_name;
    char* key_type;
    int count;
    attribute *pre;
    attribute *next;
};

class catalog {
public:
    // initialize head, tail and count
    catalog(void);
    // deconstructor
    ~catalog(void);
    // show that catalog information
    void print(void);
    // add a attribute into the cataglog and return its _id
    int index(char* key_type, char* key_name);
    // search wheterh this key is already indexed, if it is, return pointer to this attribute;otherwise, return NULL;
    attribute* search(char* key_type, char* key_name);
    // search attribute by id
    attribute* search(int id);
    //get arr
    my_vector<tuple*>& getarr();
    // cout t in json type;
    void print_tuple(tuple* t);
    // sort the key with aid using binary sort
    tuple* sort_id(tuple* t);
    char* search_id(int id);
    // to find A= B.
    void Find();
    void find(char* key_name, const int& key_value);
    void find(char* key_name, const char* key_value);
    void find(char* key_name, my_vector<my_string>& key_value);
    void find(char* key_name, const bool& key_value);
    void find(char* key_name, tuple& key_value);
    // return how many key_names had been scan
    int find_int(tuple* t, const int id, const int& key_value, bool& is_find);
    int find_char(tuple* t, const int id, const char* key_value, bool& is_find);
    int find_bool(tuple* t, const int id, const bool& key_value, bool& is_find);
    int find_nested_arr(tuple* t, const int id, my_vector<my_string>& key_value, bool& is_find);
    int find_nested_obj(tuple* t, const int id, tuple& key_value, bool& is_find);

private:
    attribute* head;
    attribute* tail;
    int count;
    my_vector<tuple*> arr;
};

#endif
