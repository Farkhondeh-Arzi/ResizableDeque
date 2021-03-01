#ifndef RDQ_TESTER_H
#define RDQ_TESTER_H

#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "exception.h"
#include "resizable_deque.h"

using namespace std;

class RdqTester {
public:
    RdqTester();
    ~RdqTester();

    void readInput();

private:
    stack<ResizableDeque> lists;

    bool readNextLine(ifstream& fin, ofstream& fout);

    void addList(int);
    void copyList();
    void removeList();
    void pushFront(int);
    string popFront();
    void pushBack(int);
    string popBack();
    int size();
    void clear();
    string swap();
    int capacity();
    void print(ofstream& fout);
    bool isEmpty();
};

#endif

RdqTester::RdqTester() : lists() {

}

RdqTester::~RdqTester() {
    lists = stack<ResizableDeque>();
}

void RdqTester::readInput() {
    ifstream fin;
    fin.open("input.txt");

    ofstream fout;
    fout.open("output.txt");

    while (readNextLine(fin, fout));

    fin.close();
    fout.close();
}

bool RdqTester::readNextLine(ifstream& fin, ofstream& fout) {
    string inputLine;
    if (getline(fin, inputLine)) {
        stringstream ss(inputLine);

        string command = "";
        if (ss.good()) {
            ss >> command;

            if (command == "") return true;
            else if (command == "new") {
                int param = 0;
                if (ss.good()) ss >> param;

                addList(param);
            }
            else if (command == "exit") return false;
            else if (command == "copy") copyList();
            else if (command == "end") {
                removeList();
                if (lists.empty()) return false;
            }
            else if (command == "size") fout << size() << endl;
            else if (command == "cap") fout << capacity() << endl;
            else if (command == "print") print(fout);
            else if (command == "empty") fout << std::boolalpha << isEmpty() << endl;
            else if (command == "clear") clear();
            else if (command == "swap") fout << std::boolalpha << swap() << endl;
            else if (command == "pop_front") fout << popFront() << endl;
            else if (command == "pop_back") fout << popBack() << endl;
            else {
                int param;
                if (ss.good()) ss >> param;
                else throw IllegalArgument();

                if (command == "push_front") pushFront(param);
                else if (command == "push_back") pushBack(param);
            }
            return true;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

void RdqTester::addList(int capacity) {
    ResizableDeque newList = capacity == 0 ? ResizableDeque() : ResizableDeque(capacity);
    lists.push(newList);
}

void RdqTester::copyList() {
    ResizableDeque newList(lists.top());
    lists.push(newList);
}

void RdqTester::removeList() {
    lists.pop();
}

void RdqTester::pushFront(int val) {
    lists.top().pushFront(val);
}

string RdqTester::popFront() {
    try {
        int val = lists.top().front();
        lists.top().popFront();
        return to_string(val);
    }
    catch (Underflow ex) {
        return "empty";
    }
    catch (Exception ex) {
        return "error";
    }
    return "none";
}

void RdqTester::pushBack(int val) {
    lists.top().pushBack(val);
}

string RdqTester::popBack() {
    try {
        int val = lists.top().back();
        lists.top().popBack();
        return to_string(val);
    }
    catch (Underflow ex) {
        return "empty";
    }
    catch (Exception ex) {
        return "error";
    }
    return "none";
}

int RdqTester::size() {
    return lists.top().size();
}

void RdqTester::clear() {
    lists.top().clear();
}

string RdqTester::swap() {
    if (lists.size() < 2) return "less than 2 lists";
    ResizableDeque list2 = lists.top();
    lists.pop();
    ResizableDeque list1 = lists.top();
    lists.pop();

    list1.swap(list2);

    lists.push(list1);
    lists.push(list2);
    return "swapped";
}

int RdqTester::capacity() {
    return lists.top().capacity();
}

void RdqTester::print(ofstream& fout) {
    fout << lists.top() << endl;
}

bool RdqTester::isEmpty() {
    return lists.top().empty();
}