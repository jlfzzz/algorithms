//
// Created by 123 on 25-5-27.
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
  vector<string> path;
  string smallestFromLeaf(TreeNode* root) {
    dfs(root, "");
    sort(path.begin(), path.end()); // 升序排序
    return path[0];
  }

  void dfs(TreeNode* root, string s) {
    if (!root)
      return;
    s += 'a' + root->val;
    if (!root->left && !root->right) {
      reverse(s.begin(), s.end()); // 题目要求从根节点到叶节点，因此反转
      path.push_back(s);
      return;
    }
    dfs(root->left, s);
    dfs(root->right, s);
  }
};