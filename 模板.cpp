#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

struct ListNode {
	int val;
	ListNode *next;

	ListNode() : val(0), next(nullptr) {
	}

	explicit ListNode(int x) : val(x), next(nullptr) {
	}

	ListNode(int x, ListNode *next) : val(x), next(next) {
	}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {
	}
};


