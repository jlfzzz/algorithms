//
// Created by 123 on 25-6-8.
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
	int get_height(TreeNode* node) {
		if (node == nullptr) {
			return 0;
		}
		int left_h = get_height(node->left);
		if (left_h == -1) {
			return -1; // 提前退出，不再递归
		}
		int right_h = get_height(node->right);
		if (right_h == -1 || abs(left_h - right_h) > 1) {
			return -1;
		}
		return max(left_h, right_h) + 1;
	}

public:
	bool isBalanced(TreeNode* root) {
		return get_height(root) != -1;
	}
};