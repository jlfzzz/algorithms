#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	string longestPrefix(string s) {
		int n = s.size();
		vector<int> next(n, 0);
		int i = 1;
		int len = 0;
		while (i < n) {
			while (len > 0 && s[i] != s[len]) {
				len = next[len - 1];
			}
			if (s[i] == s[len]) {
				len++;
			}
			next[i] = len;
			i++;
		}
		return s.substr(0, next.back());
	}
};

class Solution {
public:
	string longestPrefix(string s) {
		int n = s.size();
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
		for (int i = 1; i <= n; i++) H[i] = (H[i - 1] * BASE + s[i - 1] - 'a') % MOD;

		auto query = [&](int L, int R) {
			return (H[R] - H[L - 1] * P[R - L + 1] % MOD + MOD) % MOD;
		};
		// 字符串哈希模板结束
		int ans = 0;
		for (int i = 1; i < n; i += 1) {
			int len = n - i;
			// 判断从第 i + 1 个字符开始的后缀是不是原字符串的前缀
			if (query(1, len) == query(i + 1, n) && len > ans) ans = len;
		}
		return s.substr(0, ans);
	}
};
