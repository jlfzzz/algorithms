//
// Created by 123 on 25-7-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 操你妈记得给死妈老师排序

void solve() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<int> teachers(m);
	for (int i = 0; i < m; i++) {
		cin >> teachers[i];
	}
	ranges::sort(teachers);
	int pos;
	cin >> pos;

	auto it = lower_bound(teachers.begin(), teachers.end(), pos);
	if (it == teachers.end()) {
		cout << n - *(it - 1) << '\n';
		return;
	}

	if (it == teachers.begin()) {
		if (pos < *it)
			cout << *it - 1 << '\n';
		else
			cout << 0 << '\n';
		return;
	}

	int left = *(it - 1);
	int right = *it;

	if (pos == left or pos == right) {
		cout << 0 << '\n';
		return;
	}

	cout << (right - left) / 2 << endl;
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
