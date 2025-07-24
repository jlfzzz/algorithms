//
// Created by 123 on 25-5-26.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

c /**
   * Definition for a binary tree node.
   * struct TreeNode {
   *     int val;
   *     TreeNode *left;
   *     TreeNode *right;
   *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
   *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
   * };
   */
    /**
     * Definition for a binary tree node.
     * struct TreeNode {
     *     int val;
     *     TreeNode *left;
     *     TreeNode *right;
     *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
     * };
     */
    class Solution {
public:
  int sumEvenGrandparent(TreeNode *root) {
    int ans = 0;
    auto dfs = [&](this auto &&dfs, TreeNode *node) -> void {
      if (!node)
        return;
      if (node->val % 2 == 0) {
        if (node->left) {
          if (node->left->left) {
            ans += node->left->left->val;
          }
          if (node->left->right) {
            ans += node->left->right->val;
          }
        }
        if (node->right) {
          if (node->right->left) {
            ans += node->right->left->val;
          }
          if (node->right->right) {
            ans += node->right->right->val;
          }
        }
      }
      dfs(node->left);
      dfs(node->right);
    };
    dfs(root);
    return ans;
  }
};
