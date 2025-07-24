//
// Created by 123 on 25-5-31.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    	dp[0][0] = true;
		for (int i = 2; i <= m; i++) {
			if (p[i - 1] == '*') {
				dp[0][i] = dp[0][i] || dp[0][i - 2];
			}
		}

    	for (int i = 1; i <= n; i++) {
    		for (int j = 1; j <= m; j++) {
    			if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
    				dp[i][j] = dp[i - 1][j - 1] || dp[i][j];
    			} else if (p[j - 1] == '*') {
    				dp[i][j] = dp[i][j - 2];
    				if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
    					dp[i][j] = dp[i][j] || dp[i - 1][j];
    				}
    			}
    		}
    	}
    	return dp[n][m];
    }
};

class Solution {
public:
	bool isMatch(string s, string p) {
		int n = s.size();
		int m = p.size();
		vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
		dp[0][0] = true;

		// 初始化空串匹配 p 的前缀
		for (int j = 2; j <= m; j++) {
			if (p[j - 1] == '*') {
				dp[0][j] = dp[0][j - 2];
			}
		}

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				} else if (p[j - 1] == '*') {
					// 0 occurrence
					dp[i][j] = dp[i][j - 2];
					// 1 or more occurrences
					if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
						dp[i][j] = dp[i][j] || dp[i - 1][j];
					}
				}
			}
		}

		return dp[n][m];
	}
};
