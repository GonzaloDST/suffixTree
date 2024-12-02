#include "node.h"

Node::Node(int start, int end): start(start), end(end), parent(nullptr) {}
Node::~Node(){
    delete parent;
    for(auto &child:children){
        delete child.second;
    }
}
bool Node::isLeaf() const {
        return children.empty();
    }
int Node::size(){
        return (this->end - this->start + 1);
    }
