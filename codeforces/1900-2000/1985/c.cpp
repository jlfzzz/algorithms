//
// Created by 123 on 25-7-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int ans = a[0] == 0 ? 1 : 0;
	int left_mx = a[0];
	ll pre_sum = 1LL * a[0];
	for (int i = 1; i < n; i++) {
		int x = a[i];
		if (x >= left_mx and pre_sum == x) {
			ans += 1;
		} else if (x <= left_mx and left_mx == pre_sum + x - left_mx) {
			ans += 1;
		}
		left_mx = max(left_mx, x);
		pre_sum += 1LL * x;
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
