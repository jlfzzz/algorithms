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
	int maxAdjacentDistance(vector<int>& nums) {
        int n = nums.size();
		int ans = INT_MIN;

		for (int i = 1; i < n; i++) {
			ans = max(ans, abs(nums[i] - nums[i - 1]));
		}
		ans = max(ans, abs(nums[0] - nums[n - 1]));
		return ans;
	}
};