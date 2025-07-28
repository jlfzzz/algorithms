//
// Created by 123 on 25-7-28.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

class Solution {
public:
	vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        ll n = nums.size();
		ll mx = ranges::max(nums);

		vector<ll> cnt(mx + 1,0 );
		for (ll x : nums) {
			cnt[x] += 1;
		}

		vector<ll> dp(mx + 1, 0);
		for (ll i = mx; i >= 1; i--) {
			ll t = 0;
			for (ll j = i; j <= mx; j+= i) {
				t += cnt[j];
				dp[i] -= dp[j];
			}
			dp[i] += t * (t - 1) / 2;
		}

		for (ll i = 1; i <= mx; i++) {
			dp[i] += dp[i - 1];
		}

		vector<int> ans(queries.size());
		for (ll i = 0; i < queries.size(); i++) {
			ll x = queries[i];
			ans[i] = ranges::upper_bound(dp, x) - dp.begin();
		}
		return ans;
	}
};