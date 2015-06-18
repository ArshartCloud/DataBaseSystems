#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstdlib>
#include <cassert>
using namespace std;

// a simplified implementation of dynamic array
template<typename T>
class my_vector {
public:
    my_vector(void);
    virtual ~my_vector(void);
    void add(T ele);
    T& operator[](int pos);
    void vector_release(void);
    int getSize(void);
private:
    int capacity;
    int ele_num;
    T* arr;
};

// Implementation
template<typename T>
my_vector<T>::my_vector(void) {
    capacity = 0;
    ele_num = 0;
    arr = NULL;
}

// manually release
template<typename T>
my_vector<T>::~my_vector(void) {
    //    delete[] arr;
}

template<typename T>
int my_vector<T>::getSize(void) {
    return ele_num;
}

template<typename T>
void my_vector<T>::add(T ele) {
    if (0 == capacity && NULL == arr) {
        arr = new T[1];
        capacity = 1;
    } else if (ele_num == capacity) {
        T* temp = new T[capacity * 2];
        for (int i = 0; i < ele_num; i++) {
            temp[i] = arr[i];
        }
        capacity *= 2;
        delete[] arr;
        arr = temp;
    }
    arr[ele_num++] = ele;
}

template<typename T>
void my_vector<T>::vector_release(void) {
    if (arr != NULL){
        delete[] arr;
        arr = NULL;
    }
}

template<typename T>
T& my_vector<T>::operator[](int pos) {
    assert(pos < ele_num);
    return *(arr + pos);
}

#endif /* MY_VECTOR_H */





