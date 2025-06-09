//
// Created by 123 on 25-6-1.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		int n = nums.size();
		vector<int> dp;
		int ans = 0;
		for (int x : nums) {
			auto it = lower_bound(dp.begin(), dp.end(), x);
			if (it == dp.end()) {
				dp.push_back(x);
				ans++;
			} else {
				*it = x;
			}
		}
		return ans;
	}
};

class Solution {
public:
	int lengthOfLIS(vector<int> &nums) {
		int n = (int) nums.size();
		if (n == 0) {
			return 0;
		}
		vector<int> dp(n, 0);
		for (int i = 0; i < n; ++i) {
			dp[i] = 1;
			for (int j = 0; j < i; ++j) {
				if (nums[j] < nums[i]) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}
		return *max_element(dp.begin(), dp.end());
	}
};

class Solution {
public:
	int lengthOfLIS(vector<int> &nums) {
		int n = nums.size();
		vector<int> memo(n);
		auto dfs = [&](this auto &&dfs, int i) -> int {
			int &res = memo[i]; // 注意这里是引用
			if (res > 0) {
				// 之前计算过
				return res;
			}
			for (int j = 0; j < i; j++) {
				if (nums[j] < nums[i]) {
					res = max(res, dfs(j));
				}
			}
			return ++res; // 加一提到循环外面
		};
		int ans = 0;
		for (int i = 0; i < n; i++) {
			ans = max(ans, dfs(i));
		}
		return ans;
	}
};

class Solution {
public:
	int lengthOfLIS(vector<int> &nums) {
		int n = nums.size();

		vector<vector<int> > memo(n, vector<int>(20'001, -1));
		auto dfs = [&](this auto &&dfs, int i, int j) -> int {
			if (i == n) {
				return 0;
			}

			if (memo[i][j] != -1) {
				return memo[i][j];
			}
			int x = nums[i] + 10'001;
			int res = 0;
			if (x > j) {
				res = dfs(i + 1, x) + 1;
			}
			res = max(res, dfs(i + 1, j));
			memo[i][j] = res;
			return res;
		};
		return dfs(0, 0);
	}
};
