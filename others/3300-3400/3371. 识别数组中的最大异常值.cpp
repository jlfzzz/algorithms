//
// Created by 123 on 25-5-29.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int getLargestOutlier(vector<int>& nums) {
		unordered_map<int, int> cnt;
		int total = 0;
		for (int x : nums) {
			cnt[x]++;
			total += x;
		}

		int ans = INT_MIN;
		for (int x : nums) {
			cnt[x]--;
			if ((total - x) % 2 == 0 && cnt[(total - x) / 2] > 0) {
				ans = max(ans, x);
			}
			cnt[x]++;
		}
		return ans;
	}
};
