#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstdio>
#include <cstdlib>

// a simplified implementation of dynamic array
template<typename T>
class my_vector {
public:
    my_vector();

    ~my_vector();

    void add(T ele);
    T& operator[](int pos);
private:
    int capacity;
    int ele_num;
    T* arr;
};

// Implementation
template<typename T>
my_vector<T>::my_vector() {
    capacity = 0;
    ele_num = 0;
    arr = NULL;
}

template<typename T>
my_vector<T>::~my_vector() {
    delete[] arr;
}

template<typename T>
void my_vector<T>::add(T ele) {
    if (0 == capacity && NULL == arr) {
        arr = new T[5];
        capacity = 2;
    } else if (ele_num == capacity) {
        T* temp = new T[capacity * 2];
        for (int i = 0; i < ele_num; i++) {
            temp[i] = arr[i];
        }

        capacity *= 2;
        delete[] arr;
        arr = temp;
    }
    *(arr + ele_num) = ele;
     ++ele_num;
}

template<typename T>
T& my_vector<T>::operator[](int pos) {
    if (pos < ele_num) {
        return *(arr + pos);
    }
}


#endif /* MY_VECTOR_H */





