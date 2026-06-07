// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

int main() {
    std::cout << "=== Перестановки для {1,2,3} ===" << std::endl;
    
    std::vector<char> in = {'1','2','3'};
    PMTree tree(in);
    
    std::vector<std::vector<char>> perms = getAllPerms(tree);
    for (size_t i = 0; i < perms.size(); i++) {
        std::cout << i+1 << ": ";
        for (char c : perms[i]) std::cout << c;
        std::cout << std::endl;
    }
    
    std::cout << "\n=== getPerm1 и getPerm2 ===" << std::endl;
    std::vector<char> p1 = getPerm1(tree, 2);
    std::vector<char> p2 = getPerm2(tree, 3);
    
    std::cout << "getPerm1(tree, 2): ";
    for (char c : p1) std::cout << c;
    std::cout << std::endl;
    
    std::cout << "getPerm2(tree, 3): ";
    for (char c : p2) std::cout << c;
    std::cout << std::endl;
    
    std::cout << "\n=== Эксперимент (данные для графика) ===" << std::endl;
    std::cout << "n\tgetAllPerms(ms)\tgetPerm1(ms)\tgetPerm2(ms)" << std::endl;
    
    std::vector<int> sizes = {3,4,5,6,7};
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int n : sizes) {
        std::vector<char> chars;
        for (int i = 0; i < n; i++) chars.push_back('a' + i);
        
        PMTree t(chars);
        int total = factorial(n);
        std::uniform_int_distribution<> dis(1, total);
        int rnum = dis(gen);
        
        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(t);
        auto end = std::chrono::high_resolution_clock::now();
        double timeAll = std::chrono::duration<double, std::milli>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        getPerm1(t, rnum);
        end = std::chrono::high_resolution_clock::now();
        double time1 = std::chrono::duration<double, std::milli>(end - start).count();
        
        start = std::chrono::high_resolution_clock::now();
        getPerm2(t, rnum);
        end = std::chrono::high_resolution_clock::now();
        double time2 = std::chrono::duration<double, std::milli>(end - start).count();
        
        std::cout << n << "\t" << timeAll << "\t\t" << time1 << "\t\t" << time2 << std::endl;
    }
    
    return 0;
}
