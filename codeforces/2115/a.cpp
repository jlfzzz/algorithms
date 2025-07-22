//
// Created by 123 on 25-7-22.
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

	int mx = ranges::max(a);
	vector<int> odd(mx + 1);
	vector<int> even(mx + 1);
	for (int x : a) {
		if (x & 1) {
			odd[x] = 1;
		} else {
			even[x] = 1;
		}
	}

	for (int i = 0; i <= mx; i++) {
		if (even[i] == 0) continue;
		for (int j = 0; j <= mx; j++) {
			if (odd[j] == 0) continue;
		}
	}
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