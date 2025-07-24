//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

class FenwickTree {
private:
	vector<int> tree;

public:
	FenwickTree(int n) : tree(n + 1) {
	}

	void update(int i, int diff) {
		for (; i < tree.size(); i += i & -i) {
			tree[i] += diff;
		}
	}

	int preSum(int i) {
		int s = 0;
		for (; i > 0; i -= i & -i) {
			s += tree[i];
		}
		return s;
	}

	int query(int left, int right) {
		return preSum(right + 1) - preSum(left);
	}
};

int calc(ll x) {
	int res = 0; // 修正：从 0 开始，而不是 1
	while (x > 1) {
		x = __builtin_popcountll(x);
		res += 1;
	}
	return res;
}

class Solution {
public:
	vector<int> popcountDepth(vector<long long> &nums, vector<vector<long long> > &queries) {
		int n = nums.size();
		vector<FenwickTree> tree(6, FenwickTree(n));
		for (int i = 0; i < n; i++) {
			ll x = nums[i];
			int dpt = calc(x);
			tree[dpt].update(i + 1, 1);
		}

		vector<int> ans;
		for (auto &q: queries) {
			int q1 = q[0];
			if (q1 == 1) {
				ans.emplace_back(tree[q[3]].query(q[1], q[2]));
			} else {
				ll new_val = q[2];
				ll i = q[1];
				int dpt = calc(new_val);
				tree[calc(nums[i])].update(i + 1, -1);
				tree[dpt].update(i + 1, 1);
				nums[i] = new_val;
			}
		}
		return ans;
	}
};
