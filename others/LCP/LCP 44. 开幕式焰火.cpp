//
// Created by 123 on 25-5-20.
//

#include "bits/stdc++.h"
using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  int numColor(TreeNode* root) {
    unordered_set<int> s;

    auto dfs = [&](this auto& dfs, TreeNode *node) -> void {
      if (!node) {
        return;
      }
      s.insert(node->val);
      dfs(node->left);
      dfs(node->right);
    };
    dfs(root);
    return s.size();
  }
};