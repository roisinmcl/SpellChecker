#include <cmath>
#include <iostream>
#include <sstream>

#include "LinkedList.h"

using namespace std;

//*********** Node Class Definition ***********

Node::Node() {
    next = NULL;
}

Node::Node(string w) {
    word = w;
    frequency = 0;
    next = NULL;
}

string Node::toString() {
    return word;
}

// ******** End Node Class Definition *********


// ******* Linked List Class Definition *******

LinkedList::LinkedList(const LinkedList& listToCopy) {
    head = NULL;
    tail = NULL;

    if(listToCopy.size == 0){
        return;
    } else {
        try {
            Node* ptr = listToCopy.head;
            while (ptr != NULL) {
                Node* t = new Node(*ptr);
                this->add(t);
                ptr = ptr->next;
            }

        } catch(bad_alloc err) {
            cout << "Bad allocation error." << endl;
        }
    }
}

// Overloaded default constructor
LinkedList::LinkedList() {
    size = 0;
    head = NULL;
    tail = NULL;
}

// Contructor that takes in a head Node
LinkedList::LinkedList(Node* n) {
    size = 0;
    head = n;
    tail = n;
}

// Destructor
LinkedList::~LinkedList() {
    Node* ptr = head;
    while (ptr != NULL) {
        Node* tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
}

// Copies a LinkedList to replace an existing LinkedList
void LinkedList::copyList(const LinkedList& ll) {
    head = NULL;
    tail = NULL;

    if (ll.size == 0){
        return;
    } else {
        try {
            Node* ptr = ll.head;
            while (ptr != NULL) {
                Node* t = new Node(*ptr);
                this->add(t);
                ptr = ptr->next;
            }

        } catch(bad_alloc err) {
            cout << "Bad allocation error." << endl;
        }
    }
}

// Overloaded assignment operator
LinkedList LinkedList::operator=(const LinkedList& ll) {
    LinkedList tmp_list;
    tmp_list.copyList(ll);
    return tmp_list;
}

// Adds a Node to the end of a LinkedList
void LinkedList::add(Node* n) {
    size++;
    if (head == NULL) { // List is empty, add Node to the front
        head = n;
        tail = n;
    } else { // List is not empty, add to end of list
        tail->next = n;
        tail = n;
    }
}

// Prints list in order (beginning at head, ending at tail)
void LinkedList::printList() {
    Node* ptr = head;
    if (head == NULL || size == 0) {
        cout << "Empty list." << endl;
        return;
    }
    while (size > 0 && ptr != NULL) {
        cout << ptr->toString() << endl;
        ptr = ptr->next;
    }
}

// Returns true if word is found and moved to front
// Returns false if word is not in list (misspelled word)
bool LinkedList::findAndMoveFront(string word) {
    if (head == NULL) {
        return false;
    }

    Node *found = NULL;
    Node *beforeFound = NULL;

    if (head->getWord() == word) {
        found = head;
    } else {
        Node *previous = head;
        Node *ptr = head->next;
        while (ptr != NULL) {
            if (ptr->getWord() == word) {
                found = ptr;
                beforeFound = previous;
                break;
            }
            previous = ptr;
            ptr = ptr->next;
        }
    }

    if (found == NULL) {
        return false;
    } else if (found == head) {
        found->increaseFrequency();
        return true;
    } else {
        found->increaseFrequency();
        beforeFound->next = found->next;
        found->next = head;
        head = found;
        return true;
    }
}

void LinkedList::remove(string word) {
    if (head == NULL) {
        return;
    }

    Node *found = NULL;
    Node *beforeFound = NULL;

    if (head->getWord() == word) {
        found = head;
    } else {
        Node *previous = head;
        Node *ptr = head->next;
        while (ptr != NULL) {
            if (ptr->getWord() == word) {
                found = ptr;
                beforeFound = previous;
                break;
            }
            previous = ptr;
            ptr = ptr->next;
        }
    }

    if (found == NULL) {
        return;
    } else if (found == head) {
        head = head->next;
        found = NULL;
    } else {
        beforeFound->next = found->next;
        found = NULL;
    }

}

// ******** End LinkedList Class Definition *********