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
        Node(char val) : value(val) {}
        ~Node() {
            for (auto child : children) delete child;
        }
    };
    
    Node* root;
    std::vector<char> elements;
    
    void buildTree(Node* node, std::vector<char> remaining) {
        if (remaining.empty()) return;
        
        std::sort(remaining.begin(), remaining.end());
        
        for (size_t i = 0; i < remaining.size(); ++i) {
            Node* child = new Node(remaining[i]);
            node->children.push_back(child);
            
            std::vector<char> newRemaining;
            for (size_t j = 0; j < remaining.size(); ++j) {
                if (j != i) newRemaining.push_back(remaining[j]);
            }
            buildTree(child, newRemaining);
        }
    }
    
    void collectPerms(Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result) {
        if (!node) return;
        current.push_back(node->value);
        
        if (node->children.empty()) {
            result.push_back(current);
        } else {
            for (Node* child : node->children) {
                collectPerms(child, current, result);
            }
        }
        current.pop_back();
    }
    
    void getPermByNumber(Node* node, int& counter, int target, std::vector<char>& result, bool& found) {
        if (found) return;
        result.push_back(node->value);
        
        if (node->children.empty()) {
            counter++;
            if (counter == target) found = true;
            return;
        }
        
        for (Node* child : node->children) {
            getPermByNumber(child, counter, target, result, found);
            if (found) return;
        }
        
        if (!found) result.pop_back();
    }
    
public:
    PMTree(const std::vector<char>& input) : elements(input) {
        std::vector<char> sorted = input;
        std::sort(sorted.begin(), sorted.end());
        root = new Node('\0');
        buildTree(root, sorted);
    }
    
    ~PMTree() { delete root; }
    
    std::vector<std::vector<char>> getAllPerms() {
        std::vector<std::vector<char>> result;
        std::vector<char> current;
        for (Node* child : root->children) {
            collectPerms(child, current, result);
        }
        return result;
    }
    
    std::vector<char> getPermByNumberSlow(int num) {
        if (num <= 0) return {};
        std::vector<std::vector<char>> all = getAllPerms();
        if (num > (int)all.size()) return {};
        return all[num - 1];
    }
    
    std::vector<char> getPermByNumberFast(int num) {
        if (num <= 0) return {};
        
        int total = 1;
        for (size_t i = 2; i <= elements.size(); ++i) total *= i;
        if (num > total) return {};
        
        std::vector<char> result;
        bool found = false;
        int counter = 0;
        
        for (Node* child : root->children) {
            getPermByNumber(child, counter, num, result, found);
            if (found) break;
        }
        
        return result;
    }
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);


#endif  // INCLUDE_TREE_H_
