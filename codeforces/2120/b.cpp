//
// Created by 123 on 25-7-20.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, s;
	cin >> n >> s;
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int dx, dy, x, y;
		cin >> dx >> dy >> x >> y;

		if (dx == dy) {
			if (x == y) ++ans;
		} else {
			if (x + y == s) ++ans;
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
