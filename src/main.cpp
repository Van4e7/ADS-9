// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <utility>

template<typename Func, typename... Args>
std::pair<std::vector<std::vector<char>>, long long> measureTimeAllPerms(Func func, Args... args) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<char>> result = func(args...);
    auto end = std::chrono::high_resolution_clock::now();
    return std::make_pair(result, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
}

template<typename Func, typename... Args>
std::pair<std::vector<char>, long long> measureTimePerm(Func func, Args... args) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<char> result = func(args...);
    auto end = std::chrono::high_resolution_clock::now();
    return std::make_pair(result, std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
}

int main() {
  std::vector<char> alphabet = generateAlphabet(5);
const int max_n = 9;
std::ofstream outfile("results.txt");
if (!outfile) {
    std::cerr << "Не удалось открыть файл для записи результатов\n";
    return 1;
}
outfile << "Размер алфавита | Время getAllPerms (ms) | Время getPerm1 (ms) | Время getPerm2 (ms) | Всего перестановок\n";
outfile << "------------------------------------------------------------------------------------------\n";
std::random_device rd;
std::mt19937 gen(rd());
for (int n = 1; n <= max_n; ++n) {
    std::vector<char> alphabet = generateAlphabet(n);
    PMTree tree(alphabet);
    int total_perms = tree.getTotalPermutations();
    std::uniform_int_distribution<int> dist(1, total_perms);
    int random_perm_num = dist(gen);
    std::pair<std::vector<std::vector<char>>, long long> all_perms_result = measureTimeAllPerms(getAllPerms, tree);
    long long all_perms_time = all_perms_result.second;
    std::pair<std::vector<char>, long long> perm1_result = measureTimePerm(getPerm1, tree, random_perm_num);
    long long perm1_time = perm1_result.second;
    std::pair<std::vector<char>, long long> perm2_result = measureTimePerm(getPerm2, tree, random_perm_num);
    long long perm2_time = perm2_result.second;
    outfile << n << "\t\t" << all_perms_time << "\t\t\t"
        << perm1_time << "\t\t\t" << perm2_time << "\t\t\t"
        << total_perms << "\n";
}
outfile.close();
std::cout << "Результаты сохранены в файл results.txt\n";
return 0;
}
