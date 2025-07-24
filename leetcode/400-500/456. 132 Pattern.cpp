//
// Created by 123 on 25-7-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

class Solution {
public:
	bool find132pattern(vector<int> &nums) {
		int n = nums.size();
		stack<int> candidate_k;
		candidate_k.push(nums[n - 1]);
		int max_k = INT_MIN;

		for (int i = n - 2; i >= 0; --i) {
			if (nums[i] < max_k) {
				return true;
			}
			while (!candidate_k.empty() && nums[i] > candidate_k.top()) {
				max_k = candidate_k.top();
				candidate_k.pop();
			}
			if (nums[i] > max_k) {
				candidate_k.push(nums[i]);
			}
		}

		return false;
	}
};

class Solution {
public:
	bool find132pattern(vector<int> &nums) {
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
