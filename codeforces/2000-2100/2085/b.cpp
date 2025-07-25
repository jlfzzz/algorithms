//
// Created by 123 on 25-7-25.
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
	bool flag = false;
	vector<pair<int, int> > v;
	for (int i = 0; i < n / 2; i++) {
		if (a[i] == 0) {
			flag = true;
		}
	}

	if (flag) {
		v.emplace_back(1, n / 2);
	}

	flag = false;
	for (int i = n / 2; i < n; i++) {
		if (a[i] == 0) {
			flag = true;
		}
	}
	if (flag) {
		v.emplace_back(n / 2 + 1, n);
	}
	v.emplace_back(1, n);
	cout << v.size() << '\n';
	for (auto it = v.begin(); it != v.end(); it++) {
		cout << it->first << " " << it->second << '\n';
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
