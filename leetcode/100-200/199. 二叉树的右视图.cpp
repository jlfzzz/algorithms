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
  vector<int> rightSideView(TreeNode* root) {

    vector<int> ans;
    if (!root) return ans;
    queue<TreeNode*> q;
    q.emplace(root);
    while (!q.empty()) {
      int size = q.size();
      for (int i = 0; i < size; ++i) {
        auto t = q.front();
        q.pop();
        if (t->left) {
          q.emplace(t->left);
        }
        if (t->right) {
          q.emplace(t->right);
        }
        if (i == size - 1) {
          ans.emplace_back(t->val);
        }
      }
    }
    return ans;
  }
};