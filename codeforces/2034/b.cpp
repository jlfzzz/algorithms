//
// Created by 123 on 25-7-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 双指针，不能有连续m个0

void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		a[i] = c - '0';
	}

	int cnt = 0;
	int ans = 0;
	for (int i = 0; i < n;) {
		if (a[i] == 1) {
			cnt = 0;
			i++;
		} else {
			cnt++;
			if (cnt >= m) {
				ans++;
				i += k;
				cnt = 0;
			} else {
				i++;
			}
		}
	}
	cout << ans << '\n';
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
