//
// Created by 123 on 25-6-12.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minLength(string s, int numOps) {
		int n = s.length();
		auto check = [&](int m) -> bool {
			int cnt = 0;
			if (m == 1) {
				// 改成 0101...
				for (int i = 0; i < n; i++) {
					// 如果 s[i] 和 i 的奇偶性不同，cnt 加一
					cnt += (s[i] ^ i) & 1;
				}
				// n-cnt 表示改成 1010...
				cnt = min(cnt, n - cnt);
			} else {
				int k = 0;
				for (int i = 0; i < n; i++) {
					k++;
					// 到达连续相同子串的末尾
					if (i == n - 1 || s[i] != s[i + 1]) {
						cnt += k / (m + 1);
						k = 0;
					}
				}
			}
			return cnt <= numOps;
		};
		int left = 0, right = n;
		while (left + 1 < right) {
			int mid = left + (right - left) / 2;
			(check(mid) ? right : left) = mid;
		}
		return right;
	}
};

class Solution {
public:
	int minLength(string s, int numOps) {
		int n = s.length();
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			cnt += (s[i] ^ i) & 1;
		}
		if (min(cnt, n - cnt) <= numOps) {
			return 1;
		}

		priority_queue<tuple<int, int, int> > pq;
		int k = 0;
		for (int i = 0; i < n; i++) {
			k++;
			if (i == n - 1 || s[i] != s[i + 1]) {
				pq.emplace(k, k, 1);
				k = 0;
			}
		}

		while (numOps-- && get<0>(pq.top()) > 2) {
			auto [_, k, seg] = pq.top();
			pq.pop();
			pq.emplace(k / (seg + 1), k, seg + 1);
		}
		return get<0>(pq.top());
	}
};
