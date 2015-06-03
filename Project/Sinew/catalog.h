#ifndef CATALOG_H
#define CATALOG_H

struct attribute {
    int _id;
    char* key_name;
    char* key_type;
    int count;
    struct attribute *pre;
    struct attribute *next;
};

class catalog {
public:
    // initialize head, tail and count
    catalog(void);
    // deconstructor
    ~catalog(void);
    // show that catalog information
    void print(void);
    // "find A=B"
    void find(char* key_name, void* key_value);
    // add a tuple into the cataglog
    void insert_tuple(char* key_type, char* key_name);
    // search wheterh this key is already indexed, if it is, return pointer to this attribute;otherwise, return NULL;
    attribute* search(char* key_type, char* key_name);

private:
    attribute* head;
    attribute* tail;
    int count;
};

#endif
