//
// Created by 123 on 25-6-3.
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
	vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
		vector<int> ans;
		int i = 0;
		bool flag = true;

		auto dfs = [&](this auto&& dfs, TreeNode* node) -> void {
			if (!node || !flag) return;

			// 检查当前节点值是否匹配
			if (node->val != voyage[i]) {
				flag = false;
				return;
			}
			i++;

			// 如果只有右子树或没有子树，直接递归
			if (!node->left) {
				dfs(node->right);
				return;
			}

			// 如果只有左子树，直接递归
			if (!node->right) {
				dfs(node->left);
				return;
			}

			// 两个子树都存在，判断是否需要翻转
			if (node->left->val == voyage[i]) {
				// 左子树匹配，不需要翻转
				dfs(node->left);
				dfs(node->right);
			} else if (node->right->val == voyage[i]) {
				// 右子树匹配，需要翻转
				ans.push_back(node->val);
				dfs(node->right);
				dfs(node->left);
			} else {
				// 左右子树都不匹配，无法完成
				flag = false;
				return;
			}
		};

		dfs(root);
		return flag ? ans : vector<int>({-1});
	}
};