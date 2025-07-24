//
// Created by 123 on 25-5-25.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
  int goodNodes(TreeNode* root) {
    int ans = 0;
    auto dfs = [&](this auto&& dfs, TreeNode* node, int mx) -> void {
      if (!node) return;
      if (node->val >= mx) {
        ans++;
      }
      int nxt = max(node->val, mx);
      dfs(node->left, nxt);
      dfs(node->right, nxt);
    };
    dfs(root, -100000000);
    return ans;
  }
};