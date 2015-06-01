#ifndef SERIALIZER_H
#define SERIALIZER_H

struct serializer {
    int attributes_num;
    int *aid; //  n elements
    int *offset;  // (n - 1) elements
    int len;
    char *data;
}

#endif