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
	int kIncreasing(vector<int>& arr, int k) {
		int n = arr.size();
		int ans = 0;
		for (int i = 0; i < k; i++) {
			vector<int> dp;
			for (int j = i; j < n; j += k) {
				int x = arr[j];
				auto it = ranges::upper_bound(dp, x);
				if (it == dp.end()) {
					dp.push_back(x);
				} else {
					*it = x;
					ans++;
				}
			}
		}
		return ans;
	}
};