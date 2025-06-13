//
// Created by 123 on 25-6-11.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


class Solution {
public:
	int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4) {
		int n = nums1.size();
		int ans = 0;

		unordered_map<int, int> mp;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mp[nums3[i] + nums4[j]]++;
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ans += mp[-nums1[i] - nums2[j]];
			}
		}
		return ans;
	}
};


