#ifndef UNTITLED_CONTAINER_H
#define UNTITLED_CONTAINER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

class OutOfBoundException {};


template <typename T>
class Container {
private:
    T** container;
    int capacity;
    int current_size = 0;

    void reallocate() {
        this->capacity *= 2;
        T** new_container = (T**) realloc(container, this->capacity * sizeof(T*));
        container = new_container;
    }


public:
    Container(int capacity) {
        container = (T**) malloc(capacity * sizeof (T*));
        this->capacity = capacity;
    }

    ~Container() {
        for (int i = 0; i < current_size; i++) {
            delete container[i];
        }
        free(container);
    }

    void put(T* el) {
        if (current_size  == capacity) {
            reallocate();
        }
        container[current_size] = el;
        current_size++;
    }

    int size() {
        return current_size;
    }

    T* operator [](int i) {
        if (i < 0 || i >= current_size) {
            throw OutOfBoundException();
        }
        return container[i];
    }
};


#endif //UNTITLED_CONTAINER_H
