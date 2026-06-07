// Copyright 2026 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PermutationGenerator {
 public:
    struct TreeNode {
        char value;
        std::vector<TreeNode*> children;
        explicit TreeNode(char val = '\0') : value(val) {}
    };

    TreeNode* root;
    std::vector<char> items;

    explicit PermutationGenerator(const std::vector<char>& input);
    ~PermutationGenerator();

 private:
    TreeNode* build(const std::vector<char>& remaining);
    void cleanup(TreeNode* node);
};

std::vector<std::vector<char>> extractAll(PermutationGenerator& gen);
std::vector<char> getByIndexSimple(PermutationGenerator& gen, int idx);
std::vector<char> getByIndexFast(PermutationGenerator& gen, int idx);

unsigned long long factorial(int n);

#endif  // INCLUDE_TREE_H_
