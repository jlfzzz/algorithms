//
// Created by 123 on 25-6-10.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		int n = nums.size();

		int s = 0;
		int left = 0;
		int ans = n + 1;
		for (int right = 0; right < n; right++) {
			s += nums[right];
			while (s >= target) {
				ans = min(ans, right - left + 1);
				s -= nums[left];
				left++;
			}
		}
		return ans == n + 1 ? 0 : ans;
	}
};