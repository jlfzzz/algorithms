//
// Created by 123 on 25-7-18.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, k;
	cin >> n >> k;
	if (k >= n) {
		cout << "alice\n";
		return;
	}
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];

	int window = 0;
	int left = 0;
	for (int right = 0; right < n; right++) {
		int x = a[right];
		if (x == 0) {
			++window;
		}
		if (right - left + 1 > k) {
			window -= a[left] == 0;
		}
		if (window == k) {
			
		}
	}
	cout << "alice\n";
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