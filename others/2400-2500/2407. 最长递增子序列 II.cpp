//
// Created by 123 on 25-6-12.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int lengthOfLIS(vector<int> &nums, int k) {
		int m = ranges::max(nums);
		vector<int> mx(4 * m);

		auto update = [&](this auto&&update, int o, int l, int r, int target, int val)-> void {
			if (l == r) {
				mx[o] = val;
				return;
			}

			int mid = (l + r) / 2;
			if (target <= mid) {
				update(o * 2, l, mid, target, val);
			} else {
				update(o * 2 + 1, mid + 1, r, target, val);
			}
			mx[o] = max(mx[o * 2], mx[o * 2 + 1]);
		};

		auto query_mx = [&](this auto&&query_mx,int o, int l, int r, int L, int R) -> int {
			if (L <= l && r <= R) return mx[o];

			int mid = (l + r) / 2;
			int res = 0;
			if (L <= mid) {
				res = max(res, query_mx(o * 2, l, mid, L, R));
			}
			if (R > mid) {
				res = max(res, query_mx(o * 2 + 1, mid + 1, r, L, R));
			}
			return res;
		};

		for (int x: nums) {
			if (x == 1) {
				update(1, 1, m, 1, 1);
			} else {
				int t = 1 + query_mx(1, 1, m, max(x - k, 1), x - 1);
				update(1, 1, m, x, t);
			}
		}
		return mx[1];
	}
};
