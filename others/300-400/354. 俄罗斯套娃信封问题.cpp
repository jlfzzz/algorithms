//
// Created by 123 on 25-6-8.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int maxEnvelopes(vector<vector<int>>& envelopes) {
		int n = envelopes.size();
		vector<int> dp(n);
		int ans = 0;
		ranges::sort(envelopes);

		for (int i = 0; i < n; i++) {
			dp[i] = 1;
			for (int j = 0; j < i; j++) {
				if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1]) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
			ans = max(ans, dp[i]);
		}
		return ans;
	}
};


class Solution {
public:
	int maxEnvelopes(vector<vector<int>>& envelopes) {
		sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
			if (a[0] == b[0]) return a[1] > b[1];
			return a[0] < b[0];
		});

		vector<int> dp;
		for (const auto& env : envelopes) {
			int h = env[1];
			auto it = lower_bound(dp.begin(), dp.end(), h);
			if (it == dp.end()) {
				dp.push_back(h);
			} else {
				*it = h;
			}
		}

		return dp.size();
	}
};