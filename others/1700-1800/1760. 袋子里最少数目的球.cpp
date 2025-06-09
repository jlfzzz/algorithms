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
	int minimumSize(vector<int>& nums, int maxOperations) {
		int n = nums.size();
		int lo = 1;
		int hi = ranges::max(nums) + 1;

		auto check = [&](int mx) -> bool {
			int operation = 0;
			for (int x : nums) {
				//operation += (x + mx - 1) / mx - 1;
				operation += (x - 1) / mx;
				if (operation > maxOperations) {
					return false;
				}
			}
			return operation <= maxOperations;
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