//
// Created by 123 on 25-5-22.
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
  int maxDepth(TreeNode *root) {
    int ans = 0;
    auto dfs = [&](this auto &&dfs, TreeNode *node, int depth) -> void {
      if (!node) {
        return;
      }
      ans = max(ans, depth);
      dfs(node->left, depth + 1);
      dfs(node->right, depth + 1);
    };
    dfs(root, 1);
    return ans;
  }
};
