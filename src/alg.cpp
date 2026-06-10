// Copyright 2022 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& data) {
  root = new Node();
  build(root, data);
}

void PMTree::build(Node* node, std::vector<char> elems) {
  if (elems.empty())
    return;

  for (size_t i = 0; i < elems.size(); i++) {
    Node* child = new Node(elems[i]);

    node->children.push_back(child);

    std::vector<char> next = elems;
    next.erase(next.begin() + i);

    build(child, next);
  }
}

void PMTree::clear(Node* node) {
  if (!node)
    return;

  for (Node* child : node->children)
    clear(child);

  delete node;
}

PMTree::~PMTree() {
  clear(root);
}

static void dfs(Node* node,
                std::vector<char>& current,
                std::vector<std::vector<char>>& result) {
  if (node->value != '\0')
    current.push_back(node->value);

  if (node->children.empty()) {
    if (!current.empty())
      result.push_back(current);
  } else {
    for (Node* child : node->children)
      dfs(child, current, result);
  }

  if (node->value != '\0')
    current.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;

  dfs(tree.root, current, result);

  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> perms = getAllPerms(tree);

  if (num < 1 || num > static_cast<int>(perms.size()))
    return {};

  return perms[num - 1];
}

static int factorial(int n) {
  int res = 1;

  for (int i = 2; i <= n; i++)
    res *= i;

  return res;
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result;

  int n = static_cast<int>(tree.root->children.size());

  if (num < 1 || num > factorial(n))
    return {};

  num--;

  Node* current = tree.root;

  for (int remain = n; remain > 0; remain--) {
    int block = factorial(remain - 1);

    int index = num / block;

    num %= block;

    current = current->children[index];

    result.push_back(current->value);
  }

  return result;
}
