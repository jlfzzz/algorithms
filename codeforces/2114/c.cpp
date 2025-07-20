//
// Created by 123 on 25-7-20.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {cin >> a[i];}

	int ans = 1;
	int i = 0;

	while (i < n) {
		int j = i + 1;
		while (j < n && (a[i] == a[j] || a[j] == a[i] + 1)) {
			j += 1;
		}

		if (j < n) {
			ans++;
		}
		i = j;
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