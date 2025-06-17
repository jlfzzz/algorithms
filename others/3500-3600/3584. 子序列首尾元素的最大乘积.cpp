//
// Created by 123 on 25-6-15.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	long long maximumProduct(vector<int>& nums, int m) {
		int n = nums.size();
		vector<pair<ll, ll>> dp(n + 1, pair<ll, ll>(INT_MIN, INT_MAX));
		ll ans = LONG_LONG_MIN;
		for (int i = n - 1; i >= 0; i--) {
			ll x = nums[i];
			dp[i].first = max(dp[i + 1].first,x);
			dp[i].second = min(dp[i + 1].second,x);
			if (i + m - 1 <= n - 1) {
				ans = max({ans, x * dp[i + m - 1].first, x * dp[i + m - 1].second});
			}
		}
		return ans;
	}
};