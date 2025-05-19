#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std; //

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  bool leafSimilar(TreeNode *root1, TreeNode *root2) {
    vector<int> v1;
    vector<int> v2;

    auto dfs = [&](this auto&&dfs, TreeNode *node, vector<int>& v) -> void {
      if (!node->left && !node->right) {
        v.emplace_back(node->val);
        return;
      }
      if (node->left) {
        dfs(node->left, v);
      }
      if (node->right) {
        dfs(node->right, v);
      }
    };
    dfs(root1, v1);
    dfs(root2, v2);
    return v1 == v2;
  }
};

// Created by 123 on 25-5-19.
//
