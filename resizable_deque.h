/*****************************************
* Shahrood User ID: _
* Submitted for Data Structure Course
* Department of Computer Engineering and IT
* Shahrood University of Technology
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#ifndef RESIZABLE_DEQUE_H
#define RESIZABLE_DEQUE_H

#include <algorithm>
#include <iostream>
#include "exception.h"


class ResizableDeque {
public:
    /*
     * Constructor, receives list capacity as optional input parameter,
     * If a value is not set in the parameter, the value 16 is considered.
     * If it is less than 16, capacity 16 is considered.
     */
    ResizableDeque(int = 16);

    /*
     * Copier Constructor, receives a list as input parameter,
     * Copies all it's elements in itself.
     */
    ResizableDeque(ResizableDeque const &);

    /*
     * Destructor, deletes the array.
     */
    ~ResizableDeque();

    /*
     * Returns the value in the front of the list.
     * If the list is empty, throws an underFlow error.
     */
    int front() const;

    /*
     * returns the value in the back of the list.
     * If the list is empty, throws an underFlow error.
     */
    int back() const;

    /*
     * Returns the number of elements in the list.
     */
    int size() const;

    /*
     * Returns True if the list is empty.
     */
    bool empty() const;

    /*
     * Returns the capacity of the list.
     */
    int capacity() const;

    /*
     * Moves the input ResizableDeque to itself.
     */
    void swap(ResizableDeque &);

    /*
     * Adds the input into the array in the front.
     * If the array is full, creates a new array with double size.
     */
    void pushFront(int const &);

    /*
     * Adds the input into the array in the back.
     * If the array is full, creates a new array with double size.
     */
    void pushBack(int const &);

    /*
     * Removes the initial value.
     * If the list is empty, throws an underFlow error.
     * If, after removing the value, only a quarter of the array capacity
     * is full (or less than a quarter) and the current array capacity is
     * greater than the initial capacity, creates a new array with half size.
     */
    void popFront();

    /*
     * Removes the final value
     * If the list is empty, throws an underFlow error.
     * If, after removing the value, only a quarter of the array capacity
     * is full (or less than a quarter) and the current array capacity is
     * greater than the initial capacity, creates a new array with half size.
     */
    void popBack();

    /*
     * Removes all element in array and returns capacity to the initial value.
     */
    void clear();

private:

    // Holds list elements.
    int *array;

    // Index of the front entry
    int iFront;

    // Index of the back entry
    int iBack;

    // The number of elements in the list
    int dequeSize;

    // Initial list capacity
    int initialCapacity;

    // Current list capacity
    int currCapacity;

    /*
     * Creates a new array with size of input
     * Moves all elements in old array to new array.
     */
    void resize(int);

    // Friends

    friend std::ostream &operator<<(std::ostream &, ResizableDeque const &);
};

/////////////////////////////////////////////////////////////////////////
//                   Constructors and Destructors                      //
/////////////////////////////////////////////////////////////////////////

// Constructor
ResizableDeque::ResizableDeque(int n) :
        iBack(-1),
        iFront(-1),
        dequeSize(0),
        initialCapacity(std::max(n, 16)) {

    currCapacity = initialCapacity;
    array = new int[currCapacity];
}

// Copy Constructor
ResizableDeque::ResizableDeque(ResizableDeque const &deque) :
        iBack(deque.iBack),
        iFront(deque.iFront),
        dequeSize(deque.dequeSize),
        currCapacity(deque.currCapacity),
        initialCapacity(deque.initialCapacity){

    array = new int[currCapacity];

    for (int i = 0; i < capacity(); ++i) {
        array[i] = deque.array[i];
    }
}

// Destructor
ResizableDeque::~ResizableDeque() {

    delete[] array;
}

/////////////////////////////////////////////////////////////////////////
//                     Public Member Functions                         //
/////////////////////////////////////////////////////////////////////////

int ResizableDeque::size() const {

    return dequeSize;
}

int ResizableDeque::capacity() const {

    return currCapacity;
}

bool ResizableDeque::empty() const {

    return dequeSize == 0;
}

int ResizableDeque::front() const {

    return array[iFront];
}

int ResizableDeque::back() const {

    return array[iBack];
}

void ResizableDeque::swap(ResizableDeque &deque) {

    std::swap(iBack, deque.iBack);
    std::swap(iFront, deque.iFront);
    std::swap(dequeSize, deque.dequeSize);
    std::swap(currCapacity, deque.currCapacity);
    std::swap(initialCapacity, deque.initialCapacity);
    std::swap(array, deque.array);

}

void ResizableDeque::pushFront(int const &val) {

    if (size() == capacity()) {
        resize(2 * capacity());
    }

    if (empty()) {
        iBack = capacity() - 1;
        iFront++;
    }

    if (iFront == 0) {
        iFront = capacity() - 1;

    }
    else
        iFront--;

    array[iFront] = val;
    dequeSize++;

}

void ResizableDeque::pushBack(int const &val) {

    if (size() == capacity()) {
        resize(2 * capacity());
    }

    if (empty()) {
        iFront++;
    }
    if (iBack != capacity() - 1) {
        iBack++;
    }
    else {
        iBack = 0;
    }

    array[iBack] = val;
    dequeSize++;
}

void ResizableDeque::popFront() {

    if (empty()) {
        throw Underflow();
    }

    if (iFront == capacity() - 1) iFront = 0;
    else iFront++;
    dequeSize--;

    if (size() <= (capacity() / 4) && currCapacity > initialCapacity) {
        resize(capacity() / 2);
    }
}

void ResizableDeque::popBack() {

    if (empty()) {
        throw Underflow();
    }

    if (iBack == 0) iBack = capacity() - 1;
    else iBack--;
    dequeSize--;

    if (size() <= (capacity() / 4) && currCapacity > initialCapacity) {
        resize(capacity() / 2);
    }
}

void ResizableDeque::clear() {

    iFront = -1;
    iBack = -1;
    dequeSize = 0;

    currCapacity = initialCapacity;
}


/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

void ResizableDeque::resize(int newSize) {

    int oldCapacity = currCapacity;
    currCapacity = newSize;

    int *oldArr = array;
    array = new int[currCapacity];

    if (iFront > iBack) {

        int j = 0;
        for (int i = iFront; i < oldCapacity; ++i, ++j) {
            array[j] = oldArr[i];
        }

        for (int i = 0; i <= iBack; ++i, ++j) {
            array[j] = oldArr[i];
        }

    } else {
        for (int i = iFront, j = 0; i <= iBack; ++i, ++j) {
            array[j] = oldArr[i];
        }
    }

    delete[] oldArr;

    iFront = 0;
    iBack = size() - 1;
}


/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<(std::ostream &out, ResizableDeque const &list) {

    out << "START";

    if (!list.empty()) {
        if (list.iFront > list.iBack) {

            for (int i = list.iFront; i < list.capacity(); ++i) {
                out << "->" << list.array[i];
            }

            for (int i = 0; i <= list.iBack; ++i) {
                out << "->" << list.array[i];
            }

        } else {
            for (int i = list.iFront; i <= list.iBack; ++i) {
                out << "->" << list.array[i];
            }
        }
    }

    out << "->" << "END";

    return out;
}

#endif