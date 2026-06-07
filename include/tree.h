// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
#include <algorithm>

class PMTree {
private:
    struct Node {
        char value;
        std::vector<Node*> children;
        Node(char val);
        ~Node();
    };
    
    Node* root;
    std::vector<char> elements;
    void buildTree(Node* node, std::vector<char> remaining);
    
public:
    PMTree(const std::vector<char>& input);
    ~PMTree();
    
    Node* getRoot();
    std::vector<char> getElements();
    int getElementsCount();
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
