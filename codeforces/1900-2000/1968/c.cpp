//
// Created by 123 on 25-7-25.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n;
	cin >> n;
	vector<int> b(n - 1);
	for (int i = 0; i < n - 1; i++) {
		cin >> b[i];
	}

	vector<int> a(n);
	int max_b = *max_element(b.begin(), b.end());
	a[0] = max(3, max_b + 1);  // 保证 a[0] > b[i]

	for (int i = 1; i < n; i++) {
		a[i] = a[i - 1] + b[i - 1];
	}

	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
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