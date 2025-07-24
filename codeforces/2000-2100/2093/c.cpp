//
// Created by 123 on 25-7-20.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

bool is_prime(int x) {
	if (x <= 1) {
		return false;
	}
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}

void solve() {
	int x, k;
	cin >> x >> k;
	if (k > 1 && x > 1) {
		cout << "NO";
	} else if (k == 1) {
		cout << (is_prime(x) ? "YES" : "NO");
	} else {
		cout << ((k == 2) ? "YES" : "NO");
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
