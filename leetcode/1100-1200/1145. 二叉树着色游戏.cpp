//
// Created by 123 on 25-6-2.
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
	bool btreeGameWinningMove(TreeNode *root, int n, int x) {
		int lsz, rsz;
		function<int(TreeNode *)> dfs = [&](TreeNode *node) {
			if (node == nullptr)
				return 0;
			int ls = dfs(node->left);
			int rs = dfs(node->right);
			if (node->val == x)
				lsz = ls, rsz = rs;
			return ls + rs + 1;
		};
		dfs(root);
		return max({lsz, rsz, n - 1 - lsz - rsz}) * 2 > n;
	}
};