//
// Created by 123 on 25-7-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int a1, a2, b1, b2;
	cin >> a1 >> a2 >> b1 >> b2;

	int ans = 0;

	auto cmp = [&](int a1, int a2, int b1, int b2) {
		int cnt1 = 0, cnt2 = 0;
		if (a1 > b1) {
			cnt1 += 1;
		} else if (a1 < b1) {
			cnt2 += 1;
		}
		if (a2 > b2) {
			cnt1 += 1;
		} else if (a2 < b2) {
			cnt2 += 1;
		}
		if (cnt1 > cnt2) {
			ans += 1;
		}
	};
	cmp(a1, a2, b1, b2);
	cmp(a1, a2, b2, b1);
	cmp(a2, a1, b1, b2);
	cmp(a2, a1, b2, b1);
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
