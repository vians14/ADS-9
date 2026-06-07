// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
#include <algorithm>
#include <functional>

PMTree::Node::Node(char val) : value(val) {}

PMTree::Node::~Node() {
    for (auto child : children) delete child;
}

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;
    
    std::sort(remaining.begin(), remaining.end());
    
    for (size_t i = 0; i < remaining.size(); i++) {
        Node* child = new Node(remaining[i]);
        node->children.push_back(child);
        
        std::vector<char> next;
        for (size_t j = 0; j < remaining.size(); j++) {
            if (j != i) next.push_back(remaining[j]);
        }
        buildTree(child, next);
    }
}

PMTree::PMTree(const std::vector<char>& input) : elements(input) {
    std::vector<char> sorted = input;
    std::sort(sorted.begin(), sorted.end());
    root = new Node(0);
    buildTree(root, sorted);
}

PMTree::~PMTree() {
    delete root;
}

PMTree::Node* PMTree::getRoot() {
    return root;
}

std::vector<char> PMTree::getElements() {
    return elements;
}

int PMTree::getElementsCount() {
    return elements.size();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    
    std::function<void(PMTree::Node*)> collect;
    collect = [&](PMTree::Node* node) {
        if (!node) return;
        current.push_back(node->value);
        
        if (node->children.empty()) {
            result.push_back(current);
        } else {
            for (size_t i = 0; i < node->children.size(); i++) {
                collect(node->children[i]);
            }
        }
        current.pop_back();
    };
    
    for (size_t i = 0; i < tree.getRoot()->children.size(); i++) {
        collect(tree.getRoot()->children[i]);
    }
    
    std::sort(result.begin(), result.end());
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    if (num <= 0) return std::vector<char>();
    
    std::vector<std::vector<char>> all = getAllPerms(tree);
    if (num > (int)all.size()) return std::vector<char>();
    
    return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num <= 0) return std::vector<char>();
    
    int total = 1;
    int n = tree.getElementsCount();
    for (int i = 2; i <= n; i++) total *= i;
    if (num > total) return std::vector<char>();
    
    std::vector<char> result;
    int counter = 0;
    bool found = false;
    
    std::function<void(PMTree::Node*)> dfs;
    dfs = [&](PMTree::Node* node) {
        if (found) return;
        result.push_back(node->value);
        
        if (node->children.empty()) {
            counter++;
            if (counter == num) {
                found = true;
            } else {
                result.pop_back();
            }
            return;
        }
        
        for (size_t i = 0; i < node->children.size(); i++) {
            dfs(node->children[i]);
            if (found) return;
        }
        
        if (!found) result.pop_back();
    };
    
    for (size_t i = 0; i < tree.getRoot()->children.size(); i++) {
        dfs(tree.getRoot()->children[i]);
        if (found) break;
    }
    
    return result;
}
