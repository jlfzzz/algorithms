//
// Created by 123 on 25-6-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	vector<int> findCoins(vector<int> &numWays) {
		int n = numWays.size();
		vector<int> f(n + 1);
		f[0] = 1;
		vector<int> ans;
		for (int i = 1; i <= n; i++) {
			int ways = numWays[i - 1];
			if (ways == f[i]) {
				continue;
			}
			if (ways - 1 != f[i]) {
				return {};
			}
			ans.push_back(i);
			// 现在得到了一个大小为 i 的物品，用 i 计算完全背包
			for (int j = i; j <= n; j++) {
				f[j] = min(f[j] + f[j - i], INT_MAX / 2); // 防止溢出
			}
		}
		return ans;
	}
};

class Solution {
public:
	vector<int> findCoins(vector<int>& numWays) {
		vector<int> ans;
		int n = numWays.size();

		for (int i = 0; i < n; i++) {
			int target = i + 1;
			int ways = numWays[i];
			int m = ans.size();
			vector<int> dp(target + 1);
			dp[0] = 1;
			for (int j = 0; j < m; j++) {
				int curr = ans[j];
				for (int k = curr; k <= target; k++) {
					dp[k] += dp[k - curr];
				}
			}
			if (dp[target] > ways) {
				return {};
			}
			if (dp[target] == ways) {
				continue;
			}
			if (dp[target] == ways - 1) {
				ans.push_back(target);
			} else if (dp[target] < ways - 1) {
				return {};
			}
		}
		return ans;
	}
};