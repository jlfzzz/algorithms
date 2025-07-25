//
// Created by 123 on 25-7-25.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];

	ll cnt_odd = 0;
	ll cnt_even = 0;
	for (int x: a) {
		if (x & 1) cnt_odd ++;
		else cnt_even ++;
	}
	ll ans = 0;
	if (cnt_even and cnt_odd) {
		ans = accumulate(a.begin(), a.end(), 0LL) - cnt_odd + 1;
	} else {
		ans = ranges::max(a);
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
