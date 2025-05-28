//
// Created by 123 on 25-5-28.
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
	int maxAncestorDiff(TreeNode* root) {
		int ans = 0;
		auto dfs = [&](this auto&& dfs, TreeNode* node) -> pair<int, int> {
			if (!node) {
				return {INT_MAX, INT_MIN};
			}
			auto [left_max, left_min] = dfs(node->left);
			auto [right_max, right_min] = dfs(node->right);
			int curr = node->val;
			if (left_max != INT_MAX) {
				ans = max(ans, abs(curr - left_max));
			}
			if (left_min != INT_MIN) {
				ans = max(ans, abs(curr - left_min));
			}
			if (right_max != INT_MAX) {
				ans = max(ans, abs(curr - right_max));
			}
			if (right_min != INT_MIN) {
				ans = max(ans, abs(curr - right_min));
			}
			return {max({left_max, right_max, curr}), min({left_min, right_min, curr})};
		};
		dfs(root);
		return ans;
	}
};