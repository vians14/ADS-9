// Copyright 2026 NNTU-CS
#include <algorithm>
#include <vector>
#include "tree.h"

PermutationGenerator::PermutationGenerator(const std::vector<char>& input) : items(input) {
    root = new TreeNode('\0');

    std::vector<char> sortedInput = input;
    std::sort(sortedInput.begin(), sortedInput.end());

    for (char ch : sortedInput) {
        std::vector<char> rest = sortedInput;
        auto it = std::find(rest.begin(), rest.end(), ch);
        if (it != rest.end()) {
            rest.erase(it);
        }
        TreeNode* child = build(rest);
        child->value = ch;
        root->children.push_back(child);
    }
}

PermutationGenerator::~PermutationGenerator() {
    cleanup(root);
}

PermutationGenerator::TreeNode* PermutationGenerator::build(const std::vector<char>& remaining) {
    if (remaining.empty()) {
        return new TreeNode('\0');
    }

    TreeNode* node = new TreeNode('\0');
    std::vector<char> sortedRemaining = remaining;
    std::sort(sortedRemaining.begin(), sortedRemaining.end());

    for (char ch : sortedRemaining) {
        std::vector<char> rest = sortedRemaining;
        auto it = std::find(rest.begin(), rest.end(), ch);
        if (it != rest.end()) {
            rest.erase(it);
        }
        TreeNode* child = build(rest);
        child->value = ch;
        node->children.push_back(child);
    }

    return node;
}

void PermutationGenerator::cleanup(PermutationGenerator::TreeNode* node) {
    if (!node) return;
    for (TreeNode* child : node->children) {
        cleanup(child);
    }
    delete node;
}

static void dfs(PermutationGenerator::TreeNode* cur,
                std::vector<char>& path,
                std::vector<std::vector<char>>& result,
                int depth, int limit) {
    if (depth == limit) {
        result.push_back(path);
        return;
    }
    for (PermutationGenerator::TreeNode* next : cur->children) {
        path.push_back(next->value);
        dfs(next, path, result, depth + 1, limit);
        path.pop_back();
    }
}

std::vector<std::vector<char>> extractAll(PermutationGenerator& gen) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    int total = static_cast<int>(gen.items.size());

    for (PermutationGenerator::TreeNode* first : gen.root->children) {
        path.push_back(first->value);
        dfs(first, path, result, 1, total);
        path.pop_back();
    }

    return result;
}

std::vector<char> getByIndexSimple(PermutationGenerator& gen, int idx) {
    std::vector<std::vector<char>> all = extractAll(gen);
    if (idx <= 0 || idx > static_cast<int>(all.size())) {
        return {};
    }
    return all[idx - 1];
}

unsigned long long factorial(int n) {
    unsigned long long res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }
    return res;
}

std::vector<char> getByIndexFast(PermutationGenerator& gen, int idx) {
    int total = static_cast<int>(gen.items.size());
    if (idx <= 0 || static_cast<unsigned long long>(idx) > factorial(total)) {
        return {};
    }

    std::vector<char> result;
    int remainder = idx - 1;
    PermutationGenerator::TreeNode* current = gen.root;

    for (int step = 0; step < total; ++step) {
        unsigned long long block = factorial(total - step - 1);
        int direction = remainder / static_cast<int>(block);
        remainder %= static_cast<int>(block);

        if (direction >= static_cast<int>(current->children.size())) {
            return {};
        }

        current = current->children[direction];
        result.push_back(current->value);
    }

    return result;
}
