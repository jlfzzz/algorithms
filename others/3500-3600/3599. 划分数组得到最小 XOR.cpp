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
	int minXor(vector<int>& nums, int k) {
		int n = nums.size();
		vector f(k + 1, vector<int>(n + 1, INT_MAX));
		f[0][0] = 0;
		for (int i = 1; i <= k; i++) {
			// 前后每个子数组长度至少是 1，预留空间给这些子数组
			for (int j = i; j <= n - (k - i); j++) {
				int s = 0;
				for (int l = j - 1; l >= i - 1; l--) {
					s ^= nums[l];
					f[i][j] = min(f[i][j], max(f[i - 1][l], s));
				}
			}
		}
		return f[k][n];
	}
};

class Solution {
public:
	int minXor(vector<int>& nums, int K) {
		int n = nums.size();
		vector<int> prefixXor(n + 1);
		prefixXor[0] = 0;
		for (int i = 1; i <= n; i++) {
			prefixXor[i] = prefixXor[i - 1] ^ nums[i - 1];
		}
		const int INF = 1e9;
		vector<vector<int>> dp(n + 1, vector<int>(K + 1, INF));
		dp[0][0] = 0;
		for (int i = 1; i <= n; i++) {              // 当前处理到第i个元素
			for (int j = 1; j <= min(i, K); j++) {  // 分成j段（最多分i段）
				// 枚举最后一段的起始位置
				for (int lastStart = j - 1; lastStart < i; lastStart++) {
					// 最后一段是 [lastStart+1, i]（1-indexed）
					// 对应数组下标是 [lastStart, i-1]

					// 计算最后一段的异或值
					int lastSegmentXor = prefixXor[i] ^ prefixXor[lastStart];

					// 更新dp值：取前lastStart个元素分j-1段的结果与当前段异或值的最大值
					int currentMax = max(dp[lastStart][j - 1], lastSegmentXor);
					dp[i][j] = min(dp[i][j], currentMax);
				}
			}
		}

		return dp[n][K];
	}
};