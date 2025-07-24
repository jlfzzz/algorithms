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
	int minimizeArrayValue(vector<int>& nums) {
		int n = nums.size();
		int lo = 0;
		int hi = 2e9;

		auto check = [&](int target) -> bool {
			long long have = 0;
			long long need = 0;
			for (int i = 0; i < n; i++) {
				if (nums[i] > target) {
					need += nums[i] - target;
					if (need > have) {
						return false;
					}
				} else if (nums[i] < target) {
					have += target - nums[i];
				}
			}
			return true;
		};

		int ans = 0;
		while (lo < hi) {
			int mid = lo + (hi - lo) / 2;
			if (check(mid)) {
				ans = mid;
				hi = mid;
			} else {
				lo = mid + 1;
			}
		}
		return ans;
	}
};

class Solution {
public:
	int minimizeArrayValue(vector<int>& nums) {
		int n = nums.size();
		long long ans = nums[0], s = nums[0];
		for (int i = 1; i < n; i++) {
			s += nums[i];
			ans = max(ans, (s + i) / (i + 1));
		}
		return ans;
	}
};