//
// Created by 123 on 25-5-24.
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
  int sumNumbers(TreeNode* root) {
    int ans = 0;
    auto dfs = [&](this auto&& dfs, TreeNode* node, string s) -> void {
      s += to_string(node->val);
      if (!node->left && !node->right) {
        ans += stoi(s);
        return;
      }

      if (node->left) {
        dfs(node->left, s);
      }
      if (node->right) {
        dfs(node->right, s);
      }
    };
    dfs(root, "");
    return ans;
  }
};