// Copyright 2026 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 public:
    struct Node {
        char value;
        std::vector<Node*> children;
        explicit Node(char val = '\0') : value(val) {}
    };

    Node* root;
    std::vector<char> source;

    explicit PMTree(const std::vector<char>& input);
    ~PMTree();

 private:
    Node* createSubtree(const std::vector<char>& remaining);
    void freeNode(Node* node);
};

std::vector<std::vector<char>> getAllPerms(PMTree& obj);
std::vector<char> getPerm1(PMTree& obj, int pos);
std::vector<char> getPerm2(PMTree& obj, int pos);

size_t fact(int n);

#endif  // INCLUDE_TREE_H_
