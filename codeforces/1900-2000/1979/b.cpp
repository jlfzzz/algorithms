//
// Created by 123 on 25-7-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int x, y;
	cin >> x >> y;
	int cnt = 0;
	int ans = -1;
	int i = 0;
	while ((x >> i & 1) == (y >> i & 1)) {
		i++;
		cnt++;
	}
	if (cnt != 0) {
		ans = 1 << cnt;
		cout << ans << '\n';
	} else {
		cout << 1 << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	// cout << bitset<32>(57) << endl;
	// cout << bitset<32>(37) << endl;
	// cout << bitset<32>(12) << endl;
	// cout << bitset<32>(4) << endl;
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}
