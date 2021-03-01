#include "rdq_tester.h"
#include "resizable_deque.h"
#include <iostream>

int main() {

//	RdqTester tester = RdqTester();
//	tester.readInput();

    ResizableDeque r = ResizableDeque();
    std::cout << r.capacity() << endl;

    r.pushFront(0);
    r.pushFront(1);
    r.pushFront(2);
    r.pushFront(3);
    r.pushFront(4);
    r.pushFront(5);
    r.pushFront(6);
    r.pushFront(7);
    r.pushFront(8);
    r.pushFront(9);
    r.pushFront(10);
    r.pushFront(11);
    r.pushFront(12);
    r.pushFront(13);
    r.pushFront(14);
    r.pushFront(15);
    r.pushFront(16);
    r.pushFront(17);
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;

    r.popFront();
    std::cout << r << endl;


    std::cout << r.capacity() << endl;
    return 0;
}