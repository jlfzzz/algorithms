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
	long long maxScore(int n, vector<vector<int> > &edges) {
		if (n == 1) return 1;
		if (n == 2) return 2;

		int m = edges.size();
		ll res = 0LL;
		if (m == n) {
			if (n & 1) {
				int bound = n - 1;
				for (int i = 2; i + 2 <= bound; i += 2) {
					res += 1LL * i * (i + 2);
				}
				res += 1LL * n * (n - 1);
				for (int i = 1; i + 2 <= n; i += 2) {
					res += 1LL * i * (i + 2);
				}
				if (n >= 2) {
					res += 2LL;
				}
			} else {
				for (int i = 2; i + 2 <= n; i += 2) {
					res += 1LL * i * (i + 2);
				}
				if (n >= 2) {
					res += 2LL;
				}
				for (int i = 1; i + 2 <= n; i += 2) {
					res += 1LL * i * (i + 2);
				}
				res += 1LL * n * (n - 1);
			}
		} else {
			for (int i = 1; i + 2 <= n; i += 2) {
				res += 1LL * i * (i + 2);
			}
			for (int i = 2; i + 2 <= n; i += 2) {
				res += 1LL * i * (i + 2);
			}
			res += 1LL * n * (n - 1);
		}

		return res;
	}
};

class Solution {
public:
	long long maxScore(int n, vector<vector<int>>& edges) {
		long long ans = (1LL * n * n * 2 + n * 5 - 6) * (n - 1) / 6;
		if (n == edges.size()) { // 环
			ans += 2;
		}
		return ans;
	}
};
