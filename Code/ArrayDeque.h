#ifndef ArrayDeque_h
#define ArrayDeque_h

#include "Arduino.h"

class ArrayDeque<T> {
public:
    ArrayDeque();
    int size();
    bool isEmpty();
    void addFirst(T i);
    void addLast(T i);
    T removeFirst();
    T removeLast();
    T get(int index);
    // Didn't include printDeque
private:
    int size;
    T[] item;
    int nextFirst;
    int nextLast;
    // No need to include resize or usageRatio method
};

#endif
