//
// Created by 123 on 25-7-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 要么正着一样，要么反着一样

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> b(n);
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}

	bool flag1 = true;
	for (int i = 0; i < n; i++) {
		if (a[i] != b[n - i - 1]) {
			flag1 = false;
			break;
		}
	}

	bool flag2 = true;
	for (int i = 0; i < n; i++) {
		if (a[i] != b[i]) {
			flag2 = false;
			break;
		}
	}

	if (flag1 || flag2) {
		cout << "Bob\n";
	} else {
		cout << "Alice\n";
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