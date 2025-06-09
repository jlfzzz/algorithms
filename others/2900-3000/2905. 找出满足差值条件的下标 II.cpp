//
// Created by 123 on 25-6-4.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
		int mnIndex = 0;
		int mxIndex = 0;
		int n = nums.size();
		for (int i = indexDifference; i < n; i++) {
			if (nums[i - indexDifference] > nums[mxIndex]) {
				mxIndex = i - indexDifference;
			}
			if (nums[i - indexDifference] < nums[mnIndex]) {
				mnIndex = i - indexDifference;
			}
			int x = nums[i];
			if (abs(x - nums[mnIndex]) >= valueDifference) {
				return {mnIndex, i};
			}
			if (abs(x - nums[mxIndex]) >= valueDifference) {
				return {mxIndex, i};
			}
		}
		return {-1, -1};
	}
};

class Solution {
public:
	vector<int> findIndices(vector<int>& nums, int indexDifference, int valueDifference) {
		int n = nums.size();
		vector<vector<int>> dp(n);
		int mn = INT_MAX, mx = INT_MIN;
		int mn_i = n, mx_i = n;
		for (int i = n - 1; i >= 0; i--) {
			int x = nums[i];
			dp[i] = {mn, mn_i, mx, mx_i};
			if (x < mn) {
				dp[i][0] = x;
				dp[i][1] = i;
				mn = x;
				mn_i = i;
			}
			if (x > mx) {
				dp[i][2] = x;
				dp[i][3] = i;
				mx = x;
				mx_i = i;
			}
		}

		for (int i = 0; i < n - indexDifference; i++) {
			int a = dp[i + indexDifference][0];
			int b = dp[i + indexDifference][2];
			int x = nums[i];
			if (abs(x - a) >= valueDifference) {
				return {i, dp[i + indexDifference][1]};
			} else if (abs(x - b) >= valueDifference) {
				return {i, dp[i + indexDifference][3]};
			}
		}
		return {-1, -1};
	}
};