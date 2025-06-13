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
	int minDeletionSize(vector<string>& strs) {
		int n = strs.size();
		int m = strs[0].size();
		vector<int> dp(m);
		int ans = m;
		for (int i = 0; i < m; i++) {
			dp[i] = 1;
			for (int j = 0; j < i; j++) {
				bool flag = true;
				for (int k = 0; k < n; k++) {
					if (strs[k][i] < strs[k][j]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
			ans = min(ans, m - dp[i]);
		}
		return ans;
	}
};

class Solution {
	public:
	int minDeletionSize(vector<string>& strs) {
		int n = strs.size();
		int m = strs[0].size();
		vector<int> dp(m);
		int ans = m - 1;

		for (int i = 0; i < m; i++) {
			dp[i] = 1;
			for (int j = 0; j < i; j++) {
				bool flag = true;
				for (int k = 0; k < n; k++) {
					if (strs[k][i] < strs[k][j]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					dp[i] = max(dp[i], dp[j] + 1);
					ans = min(ans, m - dp[i]);
				}
			}
		}

		return ans;
	}
};