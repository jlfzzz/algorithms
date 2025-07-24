//
// Created by 123 on 25-7-21.
//
#include <algorithm>

#include "bits/stdc++.h"
using namespace std;
using ll = long long;


class FenwickTree {
public:
	vector<int> tree;

	FenwickTree(int N) {
		tree.resize(N + 1);
	}

	void update(int index) {
		for (int i = index + 1; i < tree.size(); i += i & -i) {
			tree[i]++;
		}
	}

	int preSum(int index) {
		int s = 0;
		for (int i = index; i > 0; i -= i & -i) {
			s += tree[i];
		}
		return s;
	}
};

class Solution {
public:
	vector<int> resultArray(vector<int> &nums) {
		int n = nums.size();
		auto sorted = nums;
		ranges::sort(sorted);
		sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
		int m = sorted.size();

		vector a{nums[0]};
		vector b{nums[1]};

		FenwickTree ft1{m};
		FenwickTree ft2{m};
		auto it1 = ranges::lower_bound(sorted, nums[0]) - sorted.begin();
		auto it2 = ranges::lower_bound(sorted, nums[1]) - sorted.begin();
		ft1.update(it1);
		ft2.update(it2);

		for (int i = 2; i < n; i++) {
			int x = nums[i];
			int t = ranges::lower_bound(sorted, x) - sorted.begin();
			int s1 = a.size() - ft1.preSum(t + 1);
			int s2 = b.size() - ft2.preSum(t + 1);

			if (s1 < s2 or (s1 == s2 and b.size() < a.size())) {
				ft2.update(t);
				b.emplace_back(x);
			} else {
				ft1.update(t);
				a.emplace_back(x);
			}
		}
		a.insert(a.end(), b.begin(), b.end());
		return a;
	}
};
