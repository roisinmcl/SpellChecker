#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <stdio.h>
using namespace std;

class Node {

private:
    string word;
    int frequency;

public:
    Node* next;
    Node();
    Node(string w);
    string getWord() { return word; }
    string toString();
    int getFrequency() { return frequency; }
    void increaseFrequency() { frequency++; };
};

class LinkedList {

private:
    int size;
    void copyList(const LinkedList& ll);

public:
    Node* head;
    Node* tail;
    LinkedList();
    LinkedList(const LinkedList& ll);
    LinkedList(Node* head);
    ~LinkedList();
    void add(Node* n);
    void printList();
    LinkedList operator=(const LinkedList&);
    bool findAndMoveFront(string word);
    void remove(string word);
};

#endif /* LinkedList_h */
