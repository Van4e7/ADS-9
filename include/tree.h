// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>

class PMTree {

 public:
  struct Node {
    char value;
    std::vector<std::shared_ptr<Node>> children;
    Node(char val) : value(val) {}
  };
  PMTree(const std::vector<char>& elements);
  ~PMTree() = default;
  std::shared_ptr<Node> getRoot() const { return root; }
  int getTotalPermutations() const { return total_permutations; }
  
 private:
  std::shared_ptr<Node> root;
  int total_permutations;
  void buildTree(std::shared_ptr<Node> parent, const std::vector<char>& remaining);
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);
std::vector<char> generateAlphabet(int n);
#endif  // INCLUDE_TREE_H_
