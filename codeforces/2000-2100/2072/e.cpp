//
// Created by 123 on 25-7-28.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

int arr[505];

void init() {
	arr[0] = arr[1] = 0;
	for (int i = 2; i < 505; i++) {
		arr[i] = i * (i - 1) / 2;
	}
}

void solve() {
	int k;
	cin >> k;

	if (k == 0) {
		cout << 0 << '\n';
		return;
	}

	int cnt = 0;
	int x = 0;
	int y = 0;

	vector<pair<int, int> > v;
	while (k) {
		int t = upper_bound(arr, arr + 505, k) - arr - 1;
		cnt += t;
		k -= arr[t];
		while (t) {
			v.emplace_back(x, y);

			x += 1;
			t -= 1;
		}
		y += 1;
	}
	cout << cnt << '\n';
	for (auto &[x, y]: v) {
		cout << x << ' ' << y << '\n';
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	init();
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}
