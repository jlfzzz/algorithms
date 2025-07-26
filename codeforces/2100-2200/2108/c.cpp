//
// Created by 123 on 25-7-26.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];

	a.erase(unique(a.begin(), a.end()), a.end());

	int ans = 0;
	n = a.size();
	if (n == 1) ans = 1;
	if (n > 1 and a[0] > a[1]) {
		ans++;
	}

	if (n > 1 and a[n - 1] > a[n - 2]) {
		ans++;
	}
	for (int i = 1; i < n - 1; i++) {
		if (a[i] > a[i - 1] and a[i] > a[i + 1]) {
			ans++;
		}
	}
	cout << ans << '\n';
}

void solve2() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];

	int ans = 0;
	int i = 0;
	while (i < n) {
		int j = i + 1;
		while (j < n and a[j] >= a[j - 1]) {
			j += 1;
		}
		i = j;
		while (i < n and a[i] <= a[i - 1]) {
			i += 1;
		}
		ans++;
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
