//
// Created by 123 on 25-7-25.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	string s;
	cin >> s;

	ll ans = 0;
	ll window = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '1') {
			window++;
		} else {
			if (window != 0)
				ans += window + 1LL;
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