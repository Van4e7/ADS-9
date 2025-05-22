// Copyright 2022 NNTU-CS
#include  "tree.h"
#include <memory>
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <vector>

PMTree::PMTree(const std::vector<char>& elements) {
  if (elements.empty()) {
    root = nullptr;
    total_permutations = 0;
    return;
  }
  total_permutations = 1;
  for (size_t i = 1; i <= elements.size(); ++i) {
    total_permutations *= i;
  }
  root = std::make_shared<Node>('\0');
  buildTree(root, elements);
}

void PMTree::buildTree(std::shared_ptr<Node> parent, const std::vector<char>& remain) {
  if (remaining.empty()) {
    return;
  }
  for (size_t i = 0; i < remaining.size(); ++i) {
    auto child = std::make_shared<Node>(remaining[i]);
    parent->children.push_back(child);
    std::vector<char> new_remaining;
    for (size_t j = 0; j < remaining.size(); ++j) {
      if (j != i) {
        new_remaining.push_back(remaining[j]);
      }
    }
    buildTree(child, new_remaining);
  }
}

void collectPermutations(const std::shared_ptr<PMTree::Node>& node, std::vector<char>& curr,
  std::vector<std::vector<char>>& res) {
  if (node->value != '\0') {
    curr.push_back(node->value);
  }
  if (node->children.empty()) {
    if (!curr.empty()) {
      res.push_back(curr);
    }
  } else {
    for (const auto& child : node->children) {
      collectPermutations(child, curr, res);
    }
  }
  if (node->value != '\0') {
    curr.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  if (!tree.getRoot()) {
      return result;
  }
  std::vector<char> current;
  collectPermutations(tree.getRoot(), current, result);
  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  if (num < 1 || num > tree.getTotalPermutations()) {
    return {};
  }
  auto all_perms = getAllPerms(tree);
  return all_perms[num - 1];
}

std::vector<char> getPerm2Helper(const std::shared_ptr<PMTree::Node>& node, int& remain) {
  if (node->children.empty()) {
    if (--remain == 0) {
      return { node->value };
    }
    return {};
  }
  for (const auto& child : node->children) {
    auto result = getPerm2Helper(child, remain);
    if (!result.empty()) {
      if (node->value != '\0') {
        result.insert(result.begin(), node->value);
      }
      return result;
    }
  }
  return {};
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  if (num < 1 || num > tree.getTotalPermutations()) {
    return {};
  }
  int remaining = num;
  return getPerm2Helper(tree.getRoot(), remain);
}

std::vector<char> generateAlphabet(int n) {
  std::vector<char> alphabet;
  for (int i = 0; i < n; ++i) {
    alphabet.push_back('a' + i);
  }
  return alphabet;
}
