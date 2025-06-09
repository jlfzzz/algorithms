//
// Created by 123 on 25-6-6.
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
	TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
		if (!original) {
			return nullptr;
		}

        if (original == target) {
	        return cloned;
        }

		auto left = getTargetCopy(original->left, cloned->left, target);
		auto right = getTargetCopy(original->right, cloned->right, target);

		if (left != nullptr) {
			return left;
		} else {
			return right;
		}
	}
};