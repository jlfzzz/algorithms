//
// Created by 123 on 25-5-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  bool hasPathSum(TreeNode* root, int targetSum) {
    auto dfs = [&](this auto &&dfs, TreeNode* node, int path_sum) -> bool {
      if (!node) {
        return false;
      }
      path_sum += node->val;
      if (!node->left && !node->right) {
        return path_sum == targetSum;
      }

      return dfs(node->left, path_sum) || dfs(node->right, path_sum);
    };
    return dfs(root, 0);
  }
};