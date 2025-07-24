//
// Created by 123 on 25-5-29.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
class Solution {
public:
	bool isMatch(string s, string p) {
		int n = s.size(), m = p.size();
		vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
		dp[0][0] = true;

		// 处理 pattern 的前导 * 可以匹配空串
		for (int j = 1; j <= m; ++j) {
			if (p[j - 1] == '*') {
				dp[0][j] = dp[0][j - 1];
			}
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (p[j - 1] == '*') {
					// '*' 匹配空（dp[i][j - 1]）或匹配 s 中的一个字符（dp[i - 1][j]）
					dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
				} else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
			}
		}

		return dp[n][m];
	}
};
