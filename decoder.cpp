/*
 * decoder.cpp
 * created by: Jaspreet Bajwa
 *
 */
#include <iostream>
#include <string>
#include "decoder.h"

using namespace std;

/*
 * traverses the tree using the binary value and returns the value stored at that node.
 */
int Decoder::getAt(string binaryString) {
    Node *current;
    current = root;

    for (int i = 0; i < binaryString.length(); i++) {
        if (current == NULL) {
            return -1;
        }
        else if (binaryString.at(i) == '0') {
            current = current->left;
        }
        else if (binaryString.at(i) == '1') {
            current = current->right;
        }
    }
    if (current->isLeaf == true) {
        return current->value;
    }
    else {
        return -1;
    }
}

/*
 * based on the values in the codeTable.txt it generates the decoded huffman tree
 */
void Decoder::addLeaf(int val, string binary) {
    Node *current;
    current = root;
    for (int i = 0; i < binary.length(); i++) {
        if (binary.at(i) == '0') {
            if (current->left == NULL) {
                Node* newNode = new (struct Node);
                current->left = newNode;
            }
            current = current->left;
        }
        else if (binary.at(i) == '1') {
            if (current->right == NULL) {
                Node* newNode = new (struct Node);
                current->right = newNode;
            }
            current = current->right;
        }
    }
    current->value = val;
    current->isLeaf = true;
}

/*
 * returns the root
 */
Node* Decoder::getRoot() {
    return root;
}



