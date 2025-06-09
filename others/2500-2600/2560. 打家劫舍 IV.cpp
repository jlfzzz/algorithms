//
// Created by 123 on 25-6-5.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minCapability(vector<int>& nums, int k) {
		int n = nums.size();
		int lo = 1;
		int hi = 2e9;

		auto check = [&](int ability) -> bool {
			vector<int> dp(n + 2);
			for (int i = 0; i < n; i++) {
				dp[i + 2] = dp[i + 1];
				if (nums[i] <= ability) {
					dp[i + 2] = max(dp[i + 2], dp[i] + 1);
				}
			}
			return dp[n + 1] >= k;
		};

		int ans = 0;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (check(mid)) {
				ans = mid;
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
		return ans;
	}
};

class Solution {
public:
	int minCapability(vector<int>& nums, int k) {
		int n = nums.size();
		int lo = 1;
		int hi = ranges::max(nums) + 1;

		auto check = [&](int ability) -> bool {
			int f1 = 0, f2 = 0;
			for (int i = 0; i < n; i++) {
				int curr = f2;
				if (nums[i] <= ability) {
					curr = max(curr, f1 + 1);
				}
				f1 = f2;
				f2 = curr;
			}
			return f2 >= k;
		};

		int ans = 0;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (check(mid)) {
				ans = mid;
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
		return ans;
	}
};

class Solution {
	bool check(vector<int> &nums, int k, int mx) {
		int cnt = 0, n = nums.size();
		for (int i = 0; i < n; i++) {
			if (nums[i] <= mx) {
				cnt++; // 偷 nums[i]
				i++; // 跳过下一间房子
			}
		}
		return cnt >= k;
	}

public:
	int minCapability(vector<int> &nums, int k) {
		int left = 0, right = *max_element(nums.begin(), nums.end());
		while (left + 1 < right) { // 开区间写法
			int mid = left + (right - left) / 2;
			(check(nums, k, mid) ? right : left) = mid;
		}
		return right;
	}
};