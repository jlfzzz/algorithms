//
// Created by 123 on 25-5-27.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
		int n = fruits.size();
		vector<int> sum(n + 1);
		vector<int> indices(n);
		for (int i = 0; i < n; i++) {
			sum[i + 1] = sum[i] + fruits[i][1];
			indices[i] = fruits[i][0];
		}
		int ans = 0;
		for (int x = 0; x <= k / 2; x++) {
			/* 向左走 x 步，再向右走 k - x 步 */
			int y = k - 2 * x;
			int left = startPos - x;
			int right = startPos + y;
			int start = lower_bound(indices.begin(), indices.end(), left) - indices.begin();
			int end = upper_bound(indices.begin(), indices.end(), right) - indices.begin();
			ans = max(ans, sum[end] - sum[start]);
			/* 向右走 x 步，再向左走 k - x 步 */
			y = k - 2 * x;
			left = startPos - y;
			right = startPos + x;
			start = lower_bound(indices.begin(), indices.end(), left) - indices.begin();
			end = upper_bound(indices.begin(), indices.end(), right) - indices.begin();
			ans = max(ans, sum[end] - sum[start]);
		}
		return ans;
	}
};

class Solution {
public:
	int maxTotalFruits(vector<vector<int>> &fruits, int startPos, int k) {
		int left = lower_bound(fruits.begin(), fruits.end(), startPos - k, [](const auto &a, const auto b) {
			return a[0] < b;
		}) - fruits.begin();
		int right = left, s = 0, n = fruits.size();
		for (; right < n && fruits[right][0] <= startPos; right++) {
			s += fruits[right][1];
		}
		int ans = s;
		for (; right < n && fruits[right][0] <= startPos + k; ++right) {
			s += fruits[right][1]; // 枚举最右位置为 fruits[right][0]
			while (fruits[right][0] * 2 - fruits[left][0] - startPos > k &&
				   fruits[right][0] - fruits[left][0] * 2 + startPos > k)
				s -= fruits[left++][1]; // fruits[left][0] 无法到达
			ans = max(ans, s); // 更新答案最大值
		}
		return ans;
	}
};

class Solution2 {
public:
	int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
		int n = fruits.size();
		vector<int> prefix_sum(500005, 0);

		// 构建前缀和数组
		for (auto& v : fruits) {
			prefix_sum[v[0]] += v[1];
		}
		for (int i = 1; i < 500005; i++) {
			prefix_sum[i] += prefix_sum[i - 1];
		}

		int ans = 0;

		// 策略1: 先向右走i步，再向左走j步（需要往返，所以总步数是i + i + j = 2*i + j）
		for (int i = 0; i <= k; i++) {  // 向右走i步
			int right = startPos + i;
			if (right >= 500005) break;

			int remaining = k - 2 * i;  // 剩余步数用于向左
			if (remaining < 0) break;

			int left = startPos - remaining;
			if (left < 0) left = 0;

			int current = prefix_sum[right] - (left > 0 ? prefix_sum[left - 1] : 0);
			ans = max(ans, current);
		}

		// 策略2: 先向左走i步，再向右走j步（需要往返，所以总步数是i + i + j = 2*i + j）
		for (int i = 0; i <= k; i++) {  // 向左走i步
			int left = startPos - i;
			if (left < 0) break;

			int remaining = k - 2 * i;  // 剩余步数用于向右
			if (remaining < 0) break;

			int right = startPos + remaining;
			if (right >= 500005) right = 500004;

			int current = prefix_sum[right] - (left > 0 ? prefix_sum[left - 1] : 0);
			ans = max(ans, current);
		}

		return ans;
	}
};
