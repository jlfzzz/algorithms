//
// Created by 123 on 25-6-29.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minCut(string s) {
		int n = s.size();
		vector<vector<bool> > is_p(n, vector<bool>(n));
		for (int i = 0; i < n; i++) {
			is_p[i][i] = true;
			for (int j = 0; j < i; j++) {
				if (s[j] == s[i] && (is_p[j + 1][i - 1] || j + 1 == i)) {
					is_p[j][i] = true;
				}
			}
		}

		vector<int> dp(n + 1,INT_MAX);
		dp[0] = -1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				if (is_p[j- 1][i - 1]) {
					dp[i] = min(dp[i], dp[j - 1] + 1);
				}
			}
		}

		return dp[n];
	}
};
