//
// Created by 123 on 25-7-28.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, k;
	cin >> n >> k;
	string s;
	cin >> s;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int lo = 0;
	int hi = 1e9 + 5;
	int ans = -1;
	while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		auto check = [&](int limit)-> bool {
			int left = k;
			char prev = 'R';
			for (int i = 0; i < n; i++) {
				if (a[i] > limit) {
					if (s[i] == 'B' and prev == 'R') {
						left -= 1;
					}
					prev = s[i];
				}
			}
			return left >= 0;
		};
		if (check(mid)) {
			ans = mid;
			hi = mid;
		} else {
			lo = mid + 1;
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
