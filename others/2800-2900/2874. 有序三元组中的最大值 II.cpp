//
// Created by 123 on 25-5-27.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	long long maximumTripletValue(vector<int> &nums) {
		int n = nums.size();
		vector<int> suf(n + 1);
		for (int i = n - 1; i > 1; i--) {
			suf[i] = max(suf[i + 1], nums[i]);
		}
		int pre = nums[0];
		long long ans = 0;
		for (int j = 1; j < n - 1; j++) {
			ans = max(ans, 1LL * (pre - nums[j]) * suf[j + 1]);
			pre = max(pre, nums[j]);
		}
		return ans;
	}
};

class Solution {
public:
	long long maximumTripletValue(vector<int> &nums) {
		int n = nums.size();
		vector<int> suf_max(n + 1);
		for (int i = n - 1; i > 1; i--) {
			suf_max[i] = max(suf_max[i + 1], nums[i]);
		}
		int pre_max = nums[0];
		ll ans = 0;
		for (int j = 1; j < n; j++) {
			ans = max(ans, 1LL * (pre_max - nums[j]) * suf_max[j + 1]);
			pre_max = max(pre_max, nums[j]);
		}
		return ans;
	}
};
