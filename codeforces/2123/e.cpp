//
// Created by 123 on 25-7-19.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

constexpr int N = 2e5 + 555;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {cin >> a[i];}

	vector<int> freq(N);
	for (int x : a) {
		freq[x]++;
	}

	int i = 0;
	while (freq[i]) ++i;

	vector ans(n + 2, 0);
	for (int MEX = i; MEX >= 0; MEX--) {
		ans[freq[MEX]]++;
		ans[n - MEX + 1]--;
	}

	for (int i = 0; i <= n; i++) {
		if (i >= 1) ans[i] += ans[i - 1];
		cout << ans[i] << ' ';
	}
	cout << '\n';
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