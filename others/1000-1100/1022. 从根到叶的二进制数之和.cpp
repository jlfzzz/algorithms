//
// Created by 123 on 25-5-29.
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
	int sumRootToLeaf(TreeNode* root) {
		int ans = 0;
		auto dfs = [&](this auto&& dfs, int path, TreeNode* node) -> void {
			int curr = node->val;
			path = (path << 1) | curr;
			if (!node->left && !node->right) {
				ans += path;
				return;
			}
			if (node->left) {
				dfs(path, node->left);
			}
			if (node->right) {
				dfs(path, node->right);
			}
		};
		dfs(0, root);
		return ans;
	}
};