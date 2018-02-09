#include "Arduino.h"
#include "ArrayDeque.h"

ArrayDeque::ArrayDeque() {
    item = (T[]) new Object[30];
    size = 0;
    nextFirst = 3;
    nextLast = 4;
}

int size() {
    return size;
}

bool isEmpty() {
    return (size == 0);
}

void addFirst(T i) {
    if (size >= item.length)  { // cpp .length func exists??
        removeLast();
    }
    item[nextFirst] = i;  // fix this size += thing
    nextFirst = ((nextFirst - 1) + item.length) % item.length;
}

void addLast(T i) {
    if (size >= item.length) {
        removeFirst();
    }
    item[nextLast] = i;   // fix this too
    nextLast = (nextLast + 1) % item.length;
}

T removeFirst() {
    if (size == 0) {
        return NULL;  // ??? same as java null ???
    }
    T firstItem = get(0);
    nextFirst = (nextFirst + 1) % item.length;
    item[nextFirst] = NULL; // dont think we need this because only storing ints
    size -= 1;  // ??? size? ??
    // no need for call to resize func
    return firstItem;
}

T removeLast() {
    if (size == 0) {
        return NULL;
    }
    T lastItem = get(size - 1);
    nextLast = ((nextLast - 1) + item.length) % item.length;
    item[nextLast] = NULL;
    size -= 1;
    return lastItem;
}

T get(int index) {
    if (index < 0 || index > size - 1 || size == 0) {
        return NULL;  // null ? ?
    }
    int itemIndex = ((nextFirst + 1) + index) % item.length;
    return item[itemIndex];
}

// no print deque here
