//
// Created by 123 on 25-7-20.
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

	vector<pair<int, int>> right(n + 1, {INT_MIN, INT_MAX});
	vector<pair<int, int>> left(n + 1, {INT_MIN, INT_MAX});
	for (int i = n - 1; i >= 0; i--) {
		int x = a[i];
		right[i].first = max(x, right[i + 1].first);
		right[i].second = min(x, right[i + 1].second);
	}
	for (int i = 0; i < n; i++) {
		int x = a[i];
		left[i + 1].first = max(x, left[i].first);
		left[i + 1].second = min(x, left[i].second);
	}

	vector<int> ans(n, 1);
	for (int i = 0; i < n; i++) {
		int l1 = left[i].first;
		int l2 = left[i].second;
		int r1 = right[i + 1].first;
		int r2 = right[i + 1].second;
		int x = a[i];
		if (l2 < x && r1 > x) {
			ans[i] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		cout << ans[i];
	}
	cout << endl;
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