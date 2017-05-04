/*
 * decoder.h
 * created by: Jaspreet Bajwa
 */
#include <iostream>
#include <string>
using namespace std;

/*
 *  Node Struct Prototype
 */

struct Node {
    struct Node *right = NULL;
    struct Node *left = NULL;
    int value;
    bool isLeaf = false;
};

/*
 *  Decode Class Prototype
 */


class Decoder {
private:
    Node* root;
public:
    Node* getRoot();
    void addLeaf(int value, string binaryString);
    int getAt(string binaryString);

    Decoder() {
        root = new (struct Node);
    }
};



