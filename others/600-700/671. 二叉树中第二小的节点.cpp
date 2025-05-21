//
// Created by 32098 on 25-5-21.
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
  int findSecondMinimumValue(TreeNode* root) {
    int ans = -1;
    int rootvalue = root->val;

    function<void(TreeNode*)> dfs = [&](TreeNode* node) {
      if (!node) {
        return;
      }
      if (ans != -1 && node->val >= ans) {
        return;
      }
      if (node->val > rootvalue) {
        ans = node->val;
      }
      dfs(node->left);
      dfs(node->right);
    };

    dfs(root);
    return ans;
  }
};

