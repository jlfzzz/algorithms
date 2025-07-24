//
// Created by 123 on 25-7-20.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++) { cin >> a[i]; }

	vector<ll> suf(n + 1, 0);
	for (ll i = n - 1; i >= 0; i--) {
		ll x = a[i];
		suf[i] = suf[i + 1] + x;
	}
	vector<ll> left_mx(n + 1, LONG_LONG_MIN);
	for (ll i = 0; i < n; i++) {
		ll x = a[i];
		left_mx[i + 1] = max(x, left_mx[i]);
	}

	for (ll i = n - 1; i >= 0; i--) {
		ll l = left_mx[i];
		ll right_s = suf[i];
		if (l != LONG_LONG_MIN and l > a[i]) {
			right_s += l - a[i];
		}
		cout << right_s << " ";
	}
	cout << endl;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ll t;
	cin >> t;
	while (t--) {
		solve();
	}
}
