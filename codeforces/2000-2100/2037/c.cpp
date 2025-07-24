//
// Created by 123 on 25-7-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 奇数相加都不是素数，偶数相加都不是素数，各放一边，中间放5，4
// n <= 4 无解

void solve() {
	int n; cin >> n;
	if (n <= 4) {
		cout << -1 << '\n';
		return;
	}

	for (int i = 1; i <= n; i++) {
		if (i % 2 and i != 5) {
			cout << i << ' ';
		}
	}
	cout << 5 << " " << 4 << " ";
	for (int i = 2; i <= n; i++) {
		if (i % 2 == 0 and i != 4) {
			cout << i << ' ';
		}
	}
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
