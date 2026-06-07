// Copyright 2026 NNTU-CS
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

int main() {
    // Демонстрация работы
    std::vector<char> demo = {'1', '2', '3'};
    PMTree demoTree(demo);

    std::vector<std::vector<char>> permutations = getAllPerms(demoTree);
    std::cout << "Все перестановки: ";
    for (const auto& seq : permutations) {
        for (char c : seq) std::cout << c;
        std::cout << " ";
    }
    std::cout << "\n\n";

    std::vector<char> first = getPerm1(demoTree, 1);
    std::cout << "getPerm1(1): ";
    for (char c : first) std::cout << c;
    std::cout << std::endl;

    std::vector<char> second = getPerm2(demoTree, 2);
    std::cout << "getPerm2(2): ";
    for (char c : second) std::cout << c;
    std::cout << "\n\n";

    // Вычислительный эксперимент
    std::cout << "n;getAllPerms(s);getPerm1(s);getPerm2(s)" << std::endl;

    std::random_device rd;
    std::mt19937 generator(rd());

    for (int n = 3; n <= 8; ++n) {
        std::vector<char> symbols;
        for (int i = 0; i < n; ++i) {
            symbols.push_back('a' + i);
        }

        PMTree tree(symbols);

        size_t total = fact(n);
        std::uniform_int_distribution<> dist(1, static_cast<int>(total));
        int target = dist(generator);

        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(tree);
        auto afterAll = std::chrono::high_resolution_clock::now();

        getPerm1(tree, target);
        auto afterFirst = std::chrono::high_resolution_clock::now();

        getPerm2(tree, target);
        auto afterSecond = std::chrono::high_resolution_clock::now();

        double timeAll = std::chrono::duration<double>(afterAll - start)
                         .count();
        double timeFirst = std::chrono::duration<double>(afterFirst - afterAll)
                           .count();
        double timeSecond = std::chrono::duration<double>(
                            afterSecond - afterFirst).count();

        std::cout << n << ";"
                  << std::fixed << std::setprecision(8) << timeAll << ";"
                  << timeFirst << ";"
                  << timeSecond << std::endl;
    }

    return 0;
}
