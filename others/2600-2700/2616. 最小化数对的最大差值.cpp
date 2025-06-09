//
// Created by 123 on 25-6-6.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minimizeMax(vector<int>& nums, int p) {
		int n = nums.size();
		ranges::sort(nums);

		auto check = [&](int diff) -> bool {
			int cnt = 0;
			for (int i = 1; i < n; i++) {
				if (nums[i] - nums[i - 1] <= diff) {
					cnt++;
					i++;
				}
			}
			return cnt >= p;
		};

		int lo = 0;
		int hi = nums[n - 1] - nums[0] + 1;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (check(mid)) {
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
		return hi;
	}
};

class Solution {
public:
	int minimizeMax(vector<int>& nums, int p) {
		int n = nums.size();
		if (p == 0) return 0;

		ranges::sort(nums);
		int lo = 0;
		int hi = nums[n - 1] - nums[0];

		auto check = [&](int limit) -> bool {
			vector<int> dp(n + 1, 0);

			for (int i = 1; i < n; i++) {
				dp[i + 1] = dp[i];

				if (nums[i] - nums[i - 1] <= limit) {
					dp[i + 1] = max(dp[i + 1], dp[i - 1] + 1);
				}
			}

			return dp[n] >= p;
		};

		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (check(mid)) {
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}

		return lo;
	}
};

class Solution {
public:
	int minimizeMax(vector<int>& nums, int p) {
		ranges::sort(nums);

		auto check = [&](int mx) -> bool {
			int cnt = 0;
			for (int i = 0; i + 1 < nums.size(); i++) {
				if (nums[i + 1] - nums[i] <= mx) { // 选 nums[i] 和 nums[i+1]
					cnt++;
					i++;
				}
			}
			return cnt >= p;
		};

		int left = -1, right = nums.back() - nums[0];
		while (left + 1 < right) {
			int mid = left + (right - left) / 2;
			(check(mid) ? right : left) = mid;
		}
		return right;
	}
};