// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

struct PMNode {
  char value;
  std::vector<PMNode*> children;

  explicit PMNode(char v) : value(v) {}
};

class PMTree {
 public:
  explicit PMTree(const std::vector<char>& data);
  ~PMTree();

  PMNode* getRoot() const;
  const std::vector<char>& getData() const;

 private:
  PMNode* root_;
  std::vector<char> data_;

  void buildTree(PMNode* node, const std::vector<char>& remain);
  void deleteTree(PMNode* node);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);

std::vector<char> getPerm1(const PMTree& tree, int num);

std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
