// Copyright 2026 NNTU-CS
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
#include "tree.h"

int main() {
    // Демонстрация работы
    std::vector<char> demoData = {'X', 'Y', 'Z'};
    PermutationGenerator demoTree(demoData);

    std::vector<std::vector<char>> allPerms = extractAll(demoTree);
    std::cout << "Все перестановки: ";
    for (const auto& seq : allPerms) {
        for (char c : seq) std::cout << c;
        std::cout << " ";
    }
    std::cout << "\n\n";

    std::vector<char> first = getByIndexSimple(demoTree, 1);
    std::cout << "getPerm1(1): ";
    for (char c : first) std::cout << c;
    std::cout << std::endl;

    std::vector<char> second = getByIndexFast(demoTree, 2);
    std::cout << "getPerm2(2): ";
    for (char c : second) std::cout << c;
    std::cout << "\n\n";

    // Вычислительный эксперимент
    std::cout << "n;getAllPerms(s);getPerm1(s);getPerm2(s)" << std::endl;

    std::random_device rd;
    std::mt19937 rng(rd());

    for (int n = 3; n <= 8; ++n) {
        std::vector<char> symbols;
        for (int i = 0; i < n; ++i) {
            symbols.push_back('a' + i);
        }
        
        PermutationGenerator tree(symbols);
        
        unsigned long long total = factorial(n);
        std::uniform_int_distribution<> dist(1, static_cast<int>(total));
        int target = dist(rng);

        auto t0 = std::chrono::high_resolution_clock::now();
        extractAll(tree);
        auto t1 = std::chrono::high_resolution_clock::now();
        
        getByIndexSimple(tree, target);
        auto t2 = std::chrono::high_resolution_clock::now();
        
        getByIndexFast(tree, target);
        auto t3 = std::chrono::high_resolution_clock::now();

        double timeAll = std::chrono::duration<double>(t1 - t0).count();
        double timeSimple = std::chrono::duration<double>(t2 - t1).count();
        double timeFast = std::chrono::duration<double>(t3 - t2).count();

        std::cout << n << ";"
                  << std::fixed << std::setprecision(8) << timeAll << ";"
                  << timeSimple << ";"
                  << timeFast << std::endl;
    }

    return 0;
}
