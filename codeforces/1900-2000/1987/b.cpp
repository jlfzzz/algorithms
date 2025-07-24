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

	int left_mx = INT_MIN;
	vector<int> temp;
 	for (int i = 0; i < n; i++) {
 		int x = a[i];
 		if (x < left_mx) {
 			temp.push_back(left_mx - x);
 		} else {
 			left_mx = x;
 		}
 	}
	ranges::sort(temp);
	ll ans = 0;
	ll prev = 0;
	int m = temp.size();
	for (int i = 0; i < m; i++) {
		ans += 1LL * (m - i + 1) * (temp[i] - prev);
		prev = temp[i];
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