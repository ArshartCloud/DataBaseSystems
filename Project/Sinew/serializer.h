#ifndef SERIALIZER_H
#define SERIALIZER_H

struct tuple {
    int attributes_num;
    int *aid; //  n elements
    int *offset;  // (n - 1) elements
    int len;
    char *data;

    struct tuple *child;  // nested_obj
    int child_CNT;  // number of nested_obj
}

#endif
