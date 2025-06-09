//
// Created by 123 on 25-6-2.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minimumOperations(vector<int>& nums) {
		int n = nums.size();
		vector<vector<int>> dp(n + 1, vector<int>(4));

		for (int i = 1; i <= n; i++) {
			int x = nums[i - 1];
			for (int j = 1; j <= 3; j++) {
				if (j < x) {
					dp[i][j] = dp[i - 1][j];
				} else {
					dp[i][j] = max(dp[i - 1][j], dp[i - 1][x] + 1);
				}
			}
		}
		return nums.size() - dp[n][3];
	}
};

class Solution {
public:
	int minimumOperations(vector<int>& nums) {
		vector<int> g;
		for (int x : nums) {
			auto it = ranges::upper_bound(g, x);
			if (it == g.end()) {
				g.push_back(x);
			} else {
				*it = x;
			}
		}
		return nums.size() - g.size();
	}
};

class Solution {
public:
	int minimumOperations(vector<int>& nums) {
		int n = nums.size();

		vector<int> dp(n, 1);
		int ans = n;

		for (int i = 0; i < n; i++) {
			//int x = nums[i];
			for (int j = 0; j < i; j++) {
				if (nums[j] <= nums[i])
					dp[i] = max(dp[i], dp[j] + 1);
			}
			ans = min(ans, n - dp[i]);
		}
		return ans;
	}
};
