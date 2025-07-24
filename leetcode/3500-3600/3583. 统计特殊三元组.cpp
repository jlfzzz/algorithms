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
	int specialTriplets(vector<int>& nums) {
        int n = nums.size();
		unordered_map<int, int> suf;
		for (int i = n - 1; i >= 1; i--) {
			suf[nums[i]]++;
		}

		unordered_map<int, int> pre;
		pre[nums[0]]++;
		ll ans = 0;
		for (int j = 1; j < n - 1; j++) {
			suf[nums[j]]--;
			if (pre.contains(nums[j] * 2) && suf.contains(nums[j] * 2)) {
				ans += (1LL * pre[nums[j] * 2] * suf[nums[j] * 2]) % MOD;
			}
			pre[nums[j]]++;
		}
		return ans % MOD;
	}
};