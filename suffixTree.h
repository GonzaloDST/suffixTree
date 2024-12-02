#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include "node.h" 

class SuffixTree {
private:
    string text;
    Node* root;
    Node* nodoActual;

    int suffix_restantes;
    int position; 

    //El pivot indica que parte del texto se esta trabajando
    int pivot;
    int size_pivot;

    void build(int index);
    void searchOccurrences(const string& pattern, vector<int>& result, Node* node, int nodoPivot);
    void retornarHojas(Node* node, vector<int>& result);
public:
    SuffixTree(const string& input);
    bool search(const string& pattern);
    vector<int> searchOccurrences(const string& pattern);
    void printSuffixTree(const SuffixTree& tree);
    void printTree(Node* node, const string& text, int level = 0);
};

#endif // SUFFIX_TREE_H