#ifndef BTree_h
#define BTree_h

#include <iostream>
#include <stdio.h>

using namespace std;

template <int M>
class BTreeNode {

public:
    const static int m = M;
    int numKeys;
    bool isLeaf;
    string keys[M];
    BTreeNode* children[M+1];
    BTreeNode();
};

template <int M>
class BTree {

private:
    void splitChildBTree(BTreeNode<M>* parent, BTreeNode<M>* child, int i);
    void insertNonFull(BTreeNode<M>* nonFullNode, string data);

public:
    int m = M;
    BTree();
    ~BTree();
    BTreeNode<M>* root;
    bool search(BTreeNode<M>* root, string data);
    void insert(BTreeNode<M>* root, string data);
    void remove(BTreeNode<M>*, string data);
    void printTreeOrdered(BTreeNode<M>* root);
};

// **************** BTreeNode Implementation **************

template <int M>
BTreeNode<M>::BTreeNode() {
    numKeys = 0;
}

// ********* End BTreeNode Implementation *****************


// ****************** BTree Implementation ****************

template <int M>
BTree<M>::BTree() {
    root = NULL;
}

template <int M>
BTree<M>::~BTree() {
    delete this->root;
}

// Searches a BTree for a given string
// Returns true if found, returns false if not found
template <int M>
bool BTree<M>::search(BTreeNode<M>* root, string data) {
    int i = 0;
    // Locate key index where data is located or child where data should be found
    while (i < root->numKeys && data > root->keys[i]) {
        i++;
    }
    // If key of this node is equal to data, data has been found
    if (i < root->numKeys && data == root->keys[i]) {
        return true;
    } else { //If data is not in this node
        if (root->isLeaf) { // If this node is a leaf, data is not in this BTree
            return false;
        } else { // Recursively call search with root = child at found index
            return search(root->children[i], data);
        }
    }
}

// Inserts a data value into the BTree as a new BTreeNode
// Inserts the value into the correct location alphabetically
template <int M>
void BTree<M>::insert(BTreeNode<M>* root, string data) {
    int m = this->m;
    BTreeNode<M>* oldRoot = this->root;
    // If the current root is empty, create a new root
    // and insert data as the first key
    if (oldRoot == NULL) {
        BTreeNode<M>* newRoot = new BTreeNode<M>();
        newRoot->keys[0] = data;
        newRoot->numKeys = 1;
        newRoot->isLeaf = true;
        this->root = newRoot;
    } else if (oldRoot->numKeys == m) { // Root node is full, need to split and create new root
        BTreeNode<M>* newRoot = new BTreeNode<M>();
        newRoot->children[0] = oldRoot;
        newRoot->isLeaf = false;
        this->root = newRoot;
        splitChildBTree(newRoot, oldRoot, 0);
        insertNonFull(newRoot, data);
    } else { // Root node is not full or null
        insertNonFull(oldRoot, data);
    }
}

// Helper method of insert
// Adds data to a non-full node
template <int M>
void BTree<M>::insertNonFull(BTreeNode<M>* node, string data) {
    //Find location where new node should be added
    // ****add node if not full -- if full, split tree
    if (node->isLeaf) { // If current node is a leaf, try add to this node
        int i = node->numKeys;
        // Find index to insert data into node
        while (i >=0 && data < node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i] = data;
        node->numKeys++;
    } else { // If node is not a leaf
        int i = node->numKeys;
        // Find index to insert data into node
        while (i >=0 && data < node->keys[i]) {
            i--;
        }
        if (node->children[i]->numKeys == m) { // If the current node is full, needs to be split
            splitChildBTree(node, node->children[i], i);
            // Finds index where data should now be inserted
            if (data > node->keys[i]) {
                i++;
            }
        }
        // Insert data into determined child of current node
        insertNonFull(node->children[i], data);
    }
}

// Helper method of insert
// Splits a node (child) and inserts the new child into parent's child at index i
// Preconditions: parent is not full, child is full,
//                i is less than parent's numKeys and is an index of parent
template <int M>
void BTree<M>::splitChildBTree(BTreeNode<M>* parent, BTreeNode<M>* child, int i) {
    // Allocates a new node to store the second half of child's keys and children
    BTreeNode<M>* newNode = new BTreeNode<M>();
    int m = this->m;
    newNode->numKeys = m/2;
    newNode->isLeaf = child->isLeaf;

    // Data that will be inserted into parent
    string medianKey = child->keys[m/2];

    // Copy second half of child's keys into first indicies of newNode
    int y = 0;
    for (int x = m/2 + 1; x < m; x++) {
        newNode->keys[y] = child->keys[x];
        y++;
    }

    // Remove second half of child's keys
    for (int x = m/2; x < m; x++) {
        child->keys[x] = "";
    }

    // If child is not a leaf, copy second half of child's children into first indicies of newNode
    if (!(child->isLeaf)) {
        int z = 0;
        for (int x = m/2 + 1; x <= m; x++) {
            newNode->children[z] = child->children[x];
            z++;
        }

        // Delete second half of child's children
        for (int x = m/2 + 1; x <= m; x++) {
            child->children[x] = NULL;
        }

        child->numKeys = m/2;
    }

    // Move keys of parent to make room for data of child being promoted
    for (int x = parent->numKeys - 1; x >= i; x--) {
        parent->keys[x+1] = parent->keys[x];
    }

    // Move children of parent to make room for newNode to be added
    for (int x = parent->numKeys; x > i; x--) {
        parent->children[x+1] = parent->children[x];
    }

    parent->children[i+1] = newNode;
    parent->keys[i] = medianKey;
    parent->numKeys++;
}

// Removes a key with specified data from the BTree rooted at node
template <int M>
void BTree<M>::remove(BTreeNode<M>* node, string data) {
    int i = 0;
    while (i < node->numKeys && data > node->keys[i]) {
        i++;
    }
    if (node->isLeaf) {
        if (data == node->keys[i]) {
            node->keys[i] = "";
            for (int j = node->numKeys - 1; j > i; j--) {
                node->keys[j-1] = node->keys[j];
            }
            node->numKeys--;
        }
    } else {
        remove(node->children[i], data);
    }

}

// Prints all non-empty keys in the BTree rooted at node in order
template <int M>
void BTree<M>::printTreeOrdered(BTreeNode<M>* node) {
    int m = this->root->m;

    if (node == NULL) {
        return;
    } else if (node->isLeaf) {
        for (int i = 0; i < m; i++) {
            string toPrint = node->keys[i];
            if (toPrint != "") {
                cout << toPrint << endl;
            }
        }
    } else {
        for (int i = 0; i <= m; i++) {
            printTreeOrdered(node->children[i]);
            if (i < m) {
                string toPrint = node->keys[i];
                if (toPrint != "") {
                    cout << toPrint << endl;
                }
            }

        }
    }
}

// ************ End BTree Implementation ***************

#endif /* BTree_h */