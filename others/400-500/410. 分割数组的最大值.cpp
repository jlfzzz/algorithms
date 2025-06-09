//
// Created by 123 on 25-5-30.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int splitArray(vector<int>& nums, int k) {
		int n = nums.size();
		int right = reduce(nums.begin(), nums.end(), 0) + 1;
		int left = ranges::max(nums);

		auto check = [&](int limit) -> bool {
			int count = 1;
			int i = 0;
			int sum = 0;
			while (i < n) {
				int x = nums[i];
				if (sum + x > limit) {
					sum = x;
					i++;
					count++;
				} else {
					sum += x;
					i++;
				}
				if (count > k) {
					return false;
				}
			}
			return true;
		};

		int ans = -1;
		while (left < right) {
			int mid = left + (right - left) / 2;
			if (check(mid)) {
				ans = mid;
				right = mid;
			} else {
				left = mid + 1;
			}
		}
		return ans;
	}
};

class Solution {
public:
	int splitArray(vector<int> &nums, int k) {
		int left = *max_element(nums.begin(), nums.end());
		int right = accumulate(nums.begin(), nums.end(), 0);

		auto check = [&](int mx) -> bool {
			int cnt = 1, sum = 0;
			for (int x: nums) {
				if (sum + x <= mx) {
					sum += x;
				} else {
					cnt++;
					sum = x;
				}
			}
			return cnt <= k;
		};

		int ans = right;
		while (left < right) {
			int mid = left + (right - left) / 2;
			if (check(mid)) {
				ans = mid;
				right = mid; // 尝试更小
			} else {
				left = mid + 1; // 说明 mid 太小
			}
		}
		return ans;
	}
};
