//
// Created by 123 on 25-7-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 统计每一位的贡献

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	vector<int> bit_count(30);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 30; j++) {
			if (a[i] >> j & 1) {
				bit_count[j]++;
			}
		}
	}

	ll ans = 0LL;
	for (int i = 0; i < n; i++) {
		int x = a[i];
		ll curr = 0LL;
		for (int j = 0; j < 30; j++) {
			bool one = x >> j & 1;
			ll bit_value = 1LL << j;
			if (!one) {
				curr += (ll) bit_count[j] * bit_value;
			} else {
				curr += (ll) (n - bit_count[j]) * bit_value;
			}
		}
		ans = max(ans, curr);
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
