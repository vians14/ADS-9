// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>

int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

int main() {
    std::cout << std::fixed << std::setprecision(6);
    
    std::cout << "=== Permutations for {1,2,3} ===" << std::endl;
    std::vector<char> in1;
    in1.push_back('1');
    in1.push_back('2');
    in1.push_back('3');
    PMTree tree1(in1);
    
    std::vector<std::vector<char>> perms = getAllPerms(tree1);
    for (size_t i = 0; i < perms.size(); i++) {
        std::cout << i + 1 << ": ";
        for (size_t j = 0; j < perms[i].size(); j++) {
            std::cout << perms[i][j];
        }
        std::cout << std::endl;
    }
    
    std::cout << "\n=== getPerm1 and getPerm2 ===" << std::endl;
    std::vector<char> in2;
    in2.push_back('1');
    in2.push_back('3');
    in2.push_back('5');
    in2.push_back('7');
    PMTree tree2(in2);
    
    std::vector<char> p1 = getPerm1(tree2, 1);
    std::vector<char> p2 = getPerm2(tree2, 2);
    
    std::cout << "getPerm1(tree2, 1): ";
    for (size_t i = 0; i < p1.size(); i++) std::cout << p1[i];
    std::cout << std::endl;
    
    std::cout << "getPerm2(tree2, 2): ";
    for (size_t i = 0; i < p2.size(); i++) std::cout << p2[i];
    std::cout << std::endl;
    
    std::cout << "\n=== Performance experiment ===" << std::endl;
    std::cout << "n\tgetAllPerms(ms)\tgetPerm1(ms)\tgetPerm2(ms)" << std::endl;
    
    int sizes[] = {3, 4, 5, 6, 7};
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int idx = 0; idx < 5; idx++) {
        int n = sizes[idx];
        std::vector<char> chars;
        for (int i = 0; i < n; i++) chars.push_back('A' + i);
        
        PMTree tree(chars);
        int total = factorial(n);
        std::uniform_int_distribution<> dis(1, total);
        int randNum = dis(gen);
        
        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        double timeAll = std::chrono::duration<double, std::milli>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        getPerm1(tree, randNum);
        end = std::chrono::high_resolution_clock::now();
        double time1 = std::chrono::duration<double, std::milli>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        getPerm2(tree, randNum);
        end = std::chrono::high_resolution_clock::now();
        double time2 = std::chrono::duration<double, std::milli>(end - start).count();
        
        std::cout << n << "\t" << timeAll << "\t\t" << time1 << "\t\t" << time2 << std::endl;
    }
    
    return 0;
}
