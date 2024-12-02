#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct Node {
    unordered_map<char, Node*> children;
    int start, end;
    Node* parent;

    Node(int start, int end);
    ~Node();
    bool isLeaf() const;
    int size();
};

#endif // NODE_H