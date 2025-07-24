//
// Created by 123 on 25-7-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 全体平移一格

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	// if (n % 2 == 0) {
	// 	for (int i = n - 1; i >= 0; i--) {
	// 		cout << a[i] << " ";
	// 	}
	// } else {
	// 	cout << a[n / 2] << " ";
	// 	for (int i = n - 1; i >= 0; i--) {
	// 		if (i == n / 2) continue;
	// 		cout << a[i] << " ";
	// 	}
	// }
	for (int i = 0; i < n; i++) {
		cout << a[(i + 1) % n] << " ";
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
