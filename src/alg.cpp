// Copyright 2025 NNTU-CS

#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>
#include <cstdint>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& data) {
  data_ = data;
  root_ = new PMNode('\0');
  buildTree(root_, data);
}

PMTree::~PMTree() {
  deleteTree(root_);
}

PMNode* PMTree::getRoot() const {
  return root_;
}

const std::vector<char>& PMTree::getData() const {
  return data_;
}

void PMTree::deleteTree(PMNode* node) {
  if (node == nullptr)
    return;

  for (PMNode* child : node->children)
    deleteTree(child);

  delete node;
}

void PMTree::buildTree(PMNode* node,
                       const std::vector<char>& remain) {
  if (remain.empty())
    return;

  for (size_t i = 0; i < remain.size(); i++) {
    PMNode* child = new PMNode(remain[i]);
    node->children.push_back(child);

    std::vector<char> next = remain;
    next.erase(next.begin() + i);

    buildTree(child, next);
  }
}

namespace {

void dfsPerms(PMNode* node,
              std::vector<char>* current,
              std::vector<std::vector<char>>* result) {
  if (node->value != '\0')
    current->push_back(node->value);

  if (node->children.empty()) {
    if (!current->empty())
      result->push_back(*current);
  } else {
    for (PMNode* child : node->children)
      dfsPerms(child, current, result);
  }

  if (node->value != '\0')
    current->pop_back();
}

int64_t factorial(int n) {
  int64_t result = 1;

  for (int i = 2; i <= n; i++)
    result *= i;

  return result;
}

}  // namespace

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;

  dfsPerms(tree.getRoot(), &current, &result);

  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  std::vector<std::vector<char>> perms = getAllPerms(tree);

  if (num < 1 || num > static_cast<int>(perms.size()))
    return std::vector<char>();

  return perms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  const std::vector<char>& source = tree.getData();

  int n = static_cast<int>(source.size());

  if (num < 1 || num > factorial(n))
    return std::vector<char>();

  std::vector<char> available = source;
  std::vector<char> result;

  int k = num - 1;

  for (int pos = n; pos > 0; pos--) {
    int64_t block_size = factorial(pos - 1);

    int index = static_cast<int>(k / block_size);

    result.push_back(available[index]);

    available.erase(available.begin() + index);

    k %= static_cast<int>(block_size);
  }

  return result;
}
