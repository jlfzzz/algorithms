//
// Created by 123 on 25-7-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; i++) { cin >> a[i]; }
	int b;
	cin >> b;
	int left_mn = INT_MIN;
	for (int i = 0; i < n; i++) {
		int x = a[i];
		if (x < left_mn) {
			int t = b - x;
			if (t < left_mn) {
				cout << "No" << "\n";
				return;
			}
			a[i] = t;
		} else if (b - x < x and b - x >= left_mn) {
			a[i] = b - x;
		}
		left_mn = a[i];
	}
	cout << "Yes" << "\n";
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
