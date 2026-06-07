// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    return tree.getPermByNumberSlow(num);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    return tree.getPermByNumberFast(num);
}
