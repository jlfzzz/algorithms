//
// Created by 123 on 25-6-30.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
		vector<int> z(n, 0);
		int left = 0;
		int right = 0;
		for (int i = 1; i < n; i++) {
			if (i <= right) {
				z[i] = min(right - i + 1, z[i - left]);
			}
			while (i + z[i] < n && word[i + z[i]] == word[z[i]]) {
				left = i;
				right = i + z[i];
				z[i] += 1;
			}

			if (i % k == 0 && z[i] == n - i) {
				return i / k;
			}
		}
		return (n + k - 1) / k;
	}
};


class Solution {
public:
	int minimumTimeToInitialState(string word, int K) {
		int n = word.size();
		// 随机模数和基数，防止被 hack
		srand(time(nullptr));
		int MOD = 998244353 + rand() % 10007;
		int BASE = 33 + rand() % 233;

		// 字符串哈希模板开始
		long long P[n + 1];
		P[0] = 1;
		for (int i = 1; i <= n; i++) P[i] = P[i - 1] * BASE % MOD;

		long long H[n + 1];
		H[0] = 0;
		for (int i = 1; i <= n; i++) H[i] = (H[i - 1] * BASE + word[i - 1] - 'a') % MOD;

		auto query = [&](int L, int R) {
			return (H[R] - H[L - 1] * P[R - L + 1] % MOD + MOD) % MOD;
		};
		// 字符串哈希模板结束

		for (int i = K; i < n; i += K) {
			int len = n - i;
			// 判断从第 i + 1 个字符开始的后缀是不是原字符串的前缀
			if (query(1, len) == query(i + 1, n)) return i / K;
		}
		// 答案的上界
		return (n + K - 1) / K;
	}
};
