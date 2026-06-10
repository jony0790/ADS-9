// Copyright 2022 NNTU-CS

#include <chrono>
#include <iostream>
#include <vector>

#include "tree.h"

int main() {
  std::vector<char> data = {'1', '2', '3'};

  PMTree tree(data);

  std::cout << "getPerm1(1): ";
  std::vector<char> p1 = getPerm1(tree, 1);

  for (char c : p1)
    std::cout << c;
  std::cout << std::endl;

  std::cout << "getPerm2(2): ";
  std::vector<char> p2 = getPerm2(tree, 2);

  for (char c : p2)
    std::cout << c;
  std::cout << std::endl;

  std::cout << "\nTiming experiment\n";

  for (int n = 2; n <= 8; n++) {
    std::vector<char> alphabet;

    for (int i = 0; i < n; i++)
      alphabet.push_back('A' + i);

    PMTree expTree(alphabet);

    auto start1 =
        std::chrono::high_resolution_clock::now();
    getAllPerms(expTree);
    auto end1 =
        std::chrono::high_resolution_clock::now();

    auto start2 =
        std::chrono::high_resolution_clock::now();
    getPerm1(expTree, 1);
    auto end2 =
        std::chrono::high_resolution_clock::now();

    auto start3 =
        std::chrono::high_resolution_clock::now();
    getPerm2(expTree, 1);
    auto end3 =
        std::chrono::high_resolution_clock::now();

    auto t1 =
        std::chrono::duration_cast<
        std::chrono::microseconds>(
        end1 - start1).count();

    auto t2 =
        std::chrono::duration_cast<
        std::chrono::microseconds>(
        end2 - start2).count();

    auto t3 =
        std::chrono::duration_cast<
        std::chrono::microseconds>(
        end3 - start3).count();

    std::cout
        << "n = " << n
        << "  getAllPerms = " << t1
        << " us"
        << "  getPerm1 = " << t2
        << " us"
        << "  getPerm2 = " << t3
        << " us"
        << std::endl;
  }

  return 0;
}
