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
	int minOperations(vector<int>& nums) {
		int m = nums.size();
		ranges::sort(nums);
		nums.erase(ranges::unique(nums).begin(), nums.end());
		int left = 0;
		int ans = 0;

		int n = nums.size();
		for (int right = 0; right < n; right++) {
			while (nums[right] - nums[left] >= m) left++;
			ans = max(ans, right - left + 1);
		}
		return m - ans;
	}
};

class Solution {
public:
	int minOperations(vector<int>& nums) {
		int n = nums.size();
		sort(nums.begin(), nums.end());
		nums.erase(ranges::unique(nums).begin(), nums.end());
		int ans = n + 1;
		for(int i = 0; i < nums.size(); i++) {
			int left = nums[i];
			int right = left + n - 1;
			// 要将nums变成从left到right公差为1的等差数列
			int j = upper_bound(nums.begin(), nums.end(), right) - nums.begin();
			int cnt = j - i;    // 中间有cnt个属于区间[left,right]的数
			ans = min(ans, n - cnt);
		}
		return ans;
	}
};