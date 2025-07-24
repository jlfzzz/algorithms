//
// Created by 123 on 25-6-2.
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

	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
	}
};

class Solution {
public:
	int maxAns;

	/* 0 => left, 1 => right */
	void dfs(TreeNode* o, bool dir, int len) {
		maxAns = max(maxAns, len);
		if (!dir) {
			if (o->left) dfs(o->left, 1, len + 1);
			if (o->right) dfs(o->right, 0, 1);
		} else {
			if (o->right) dfs(o->right, 0, len + 1);
			if (o->left) dfs(o->left, 1, 1);
		}
	}

	int longestZigZag(TreeNode* root) {
		if (!root) return 0;
		maxAns = 0;
		dfs(root, 0, 0);
		dfs(root, 1, 0);
		return maxAns;
	}
};

class Solution {
public:
	int longestZigZag(TreeNode *root) {
		int ans = 0;
		auto dfs = [&](this auto &&dfs, TreeNode *node) -> pair<int, int> {
			if (!node) {
				return {-1e8, -1e8};
			}
			auto [leftleft, leftright] = dfs(node->left);
			auto [rightleft, rightright] = dfs(node->right);
			int left = max(0, leftright);
			int right = max(0, rightleft);
			ans = max({ans, left, right});
			return {left + 1, right + 1};
		};
		dfs(root);
		return ans;
	}
};
