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
  int pseudoPalindromicPaths (TreeNode* root) {
    vector<int> record(10, 0);
    int ans = 0;
    auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
      if (!node->left && !node->right) {
        int count = 0;
        for (int x : record) {
          if (x % 2 == 1) {
            count++;
            if (count > 1) {
              return;
            }
          }
        }
        ans++;
      }

      if (node->left) {
        record[node->left->val]++;
        dfs(node->left);
        record[node->left->val]--;
      }
      if (node->right) {
        record[node->right->val]++;
        dfs(node->right);
        record[node->right->val]--;
      }

    };
    record[root->val]++;
    dfs(root);
    return ans;
  }
};