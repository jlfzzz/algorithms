//
// Created by 123 on 25-5-30.
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
	TreeNode* addOneRow(TreeNode* root, int val, int depth) {
		if (depth == 1) {
			return new TreeNode(val, root, nullptr);
		}
		vector<TreeNode *> curLevel(1, root);
		for (int i = 1; i < depth - 1; i++) {
			vector<TreeNode *> tmpt;
			for (auto &node : curLevel) {
				if (node->left != nullptr) {
					tmpt.emplace_back(node->left);
				}
				if (node->right != nullptr) {
					tmpt.emplace_back(node->right);
				}
			}
			curLevel = move(tmpt);
		}
		for (auto &node : curLevel) {
			node->left = new TreeNode(val, node->left, nullptr);
			node->right = new TreeNode(val, nullptr, node->right);
		}
		return root;
	}
};