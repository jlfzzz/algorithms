//
// Created by 123 on 25-7-28.
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

	ll ans = a[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		if (a[i] <= ans) {
			ans += 1;
		} else {
			ans = a[i];
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