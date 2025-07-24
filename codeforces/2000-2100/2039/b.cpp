//
// Created by 123 on 25-7-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 两种情况，相邻相同或者连续3个不相同的。

void solve() {
	string s; cin >> s;
	int n = s.size();
	for (int i = 0; i + 1 < n; i++) {
		if (s[i] == s[i + 1]) {
			cout << s.substr(i, 2) << '\n';
			return;
		}
	}
	for (int i = 0; i + 2 < n; i++) {
		if (s[i] != s[i + 1] and s[i] != s[i + 2] and s[i + 1] != s[i + 2]) {
			cout << s.substr(i, 3) << '\n';
			return;
		}
	}
	cout << -1 << '\n';
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
