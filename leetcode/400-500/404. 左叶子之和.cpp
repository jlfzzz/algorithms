#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//
// Created by 123 on 25-5-21.
//

class Solution {
public:
  int sumOfLeftLeaves(TreeNode* root) {
    int ans = 0;
    auto dfs = [&](this auto&&dfs, TreeNode* node, int dir) -> void {
      if (!node) {
        return;
      }
      if (!node->left && !node->right) {
        if (dir) {
          ans += node->val;
        }
        return;
      }
      dfs(node->left, 1);
      dfs(node->right, 0);
    };
    dfs(root, 0);
    return ans;
  }
};