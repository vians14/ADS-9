// Copyright 2026 NNTU-CS
#include <algorithm>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& input) : source(input) {
    root = new Node('\0');

    std::vector<char> sortedInput = input;
    std::sort(sortedInput.begin(), sortedInput.end());

    for (char element : sortedInput) {
        std::vector<char> rest = sortedInput;
        auto iter = std::find(rest.begin(), rest.end(), element);
        if (iter != rest.end()) {
            rest.erase(iter);
        }
        Node* child = createSubtree(rest);
        child->value = element;
        root->children.push_back(child);
    }
}

PMTree::~PMTree() {
    freeNode(root);
}

PMTree::Node* PMTree::createSubtree(const std::vector<char>& remaining) {
    if (remaining.empty()) {
        return new Node('\0');
    }

    Node* currentNode = new Node('\0');
    std::vector<char> sortedRemaining = remaining;
    std::sort(sortedRemaining.begin(), sortedRemaining.end());

    for (char element : sortedRemaining) {
        std::vector<char> rest = sortedRemaining;
        auto iter = std::find(rest.begin(), rest.end(), element);
        if (iter != rest.end()) {
            rest.erase(iter);
        }
        Node* child = createSubtree(rest);
        child->value = element;
        currentNode->children.push_back(child);
    }

    return currentNode;
}

void PMTree::freeNode(PMTree::Node* node) {
    if (!node) return;
    for (Node* child : node->children) {
        freeNode(child);
    }
    delete node;
}

static void walkTree(PMTree::Node* current, std::vector<char>& buffer,
                     std::vector<std::vector<char>>& result, int depth,
                     int maxDepth) {
    if (depth == maxDepth) {
        result.push_back(buffer);
        return;
    }
    for (PMTree::Node* next : current->children) {
        buffer.push_back(next->value);
        walkTree(next, buffer, result, depth + 1, maxDepth);
        buffer.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& obj) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    int total = static_cast<int>(obj.source.size());

    for (PMTree::Node* first : obj.root->children) {
        path.push_back(first->value);
        walkTree(first, path, result, 1, total);
        path.pop_back();
    }

    return result;
}

std::vector<char> getPerm1(PMTree& obj, int pos) {
    std::vector<std::vector<char>> all = getAllPerms(obj);
    if (pos <= 0 || pos > static_cast<int>(all.size())) {
        return {};
    }
    return all[pos - 1];
}

size_t fact(int n) {
    size_t result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

std::vector<char> getPerm2(PMTree& obj, int pos) {
    int total = static_cast<int>(obj.source.size());
    if (pos <= 0 || static_cast<size_t>(pos) > fact(total)) {
        return {};
    }

    std::vector<char> result;
    int remainder = pos - 1;
    PMTree::Node* current = obj.root;

    for (int step = 0; step < total; ++step) {
        size_t blockSize = fact(total - step - 1);
        int index = remainder / static_cast<int>(blockSize);
        remainder %= static_cast<int>(blockSize);

        if (index >= static_cast<int>(current->children.size())) {
            return {};
        }

        current = current->children[index];
        result.push_back(current->value);
    }

    return result;
}
