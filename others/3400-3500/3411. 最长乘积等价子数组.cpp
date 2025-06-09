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
	int maxLength(vector<int>& nums) {
		int mx = ranges::max(nums);
		int all_lcm = 1;
		for (int x : nums) {
			all_lcm = lcm(all_lcm, x);
		}

		int ans = 0;
		for (int i = 0; i < nums.size(); i++) {
			int m = 1, l = 1, g = 0;
			for (int j = i; j < nums.size() && m <= all_lcm * mx; j++) {
				int x = nums[j];
				m *= x;
				l = lcm(l, x);
				g = gcd(g, x);
				if (m == l * g) {
					ans = max(ans, j - i + 1);
				}
			}
		}
		return ans;
	}
};

class Solution {
public:
	int maxLength(vector<int>& nums) {
		int ans = 2, mul = 1, left = 0;
		for (int right = 0; right < nums.size(); right++) {
			while (gcd(mul, nums[right]) > 1) {
				mul /= nums[left];
				left++;
			}
			mul *= nums[right];
			ans = max(ans, right - left + 1);
		}
		return ans;
	}
};