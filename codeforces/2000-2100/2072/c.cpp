//
// Created by 123 on 25-7-26.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, x;
	cin >> n >> x;

	if (n == 1) {
		cout << x << '\n';
		return;
	}

	int first_zero = 0;
	for (int i = 0; i < 31; i++) {
		if (!(x >> i & 1)) {
			first_zero = i;
			break;
		}
	}

	if (first_zero == 0) {
		vector<int> v(n, 0);
		v[0] = x;
		for (int x: v) {
			cout << x << ' ';
		}
	} else {
		int mex = 1 << first_zero;
		vector<int> v(n);
		for (int i = 0; i < min(n, mex); i++) {
			v[i] = i;
		}
		int mask = 0;
		for (int x: v) {
			mask |= x;
		}
		if (mask == x) {
			for (int x: v) {
				cout << x << ' ';
			}
		} else {
			v[n - 1] = x;
			for (int x: v) {
				cout << x << ' ';
			}
		}
	}
	cout << '\n';
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}


#include <bits/stdc++.h>

int main() {
	int t;
	std::cin >> t;
	for (; t; --t) {
		// 准备
		int n, x;
		std::cin >> n >> x;
		int sum = 0;
		std::vector<int> ans(n, 0);
		// 枚举
		for (int i = 0; i < n; ++i) {
			if ((i | x) == x) {
				// 若不会使 x 改变
				ans[i] = i;
				sum |= i; // 你过关（用这个数）
			} else break; // 否则结束枚举
		}
		if (sum != x) ans[n - 1] = x; // 不够 x，加个 x
		// 输出
		for (auto num: ans)
			std::cout << num << ' ';
		std::cout << '\n';
	}
}
