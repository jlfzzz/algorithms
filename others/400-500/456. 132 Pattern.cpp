//
// Created by 123 on 25-7-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

class Solution {
public:
	bool find132pattern(vector<int>& nums) {
		int n = nums.size();
		map<int, int> mp;
		for (int i = 1; i < n; i++) {
			mp[nums[i]]++;
		}
		int left = nums[0];
		for (int i = 1; i < n - 1; i++) {
			int x = nums[i];
			mp[x]--;
			if (mp[x] == 0) {
				mp.erase(x);
			}
			auto it = mp.upper_bound(left);
			if (left < x and it != mp.end() && it->first < x) {
				return true;
			}
			left = min(left, x);
		}
		return false;
	}
};
