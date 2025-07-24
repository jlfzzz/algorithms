//
// Created by 123 on 25-7-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 用continue不是return

void solve() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<int> teachers(m);
	for (int i = 0; i < m; i++) {
		cin >> teachers[i];
	}
	ranges::sort(teachers);
	vector<int> poss(q);
	for (int i = 0; i < q; i++) {
		cin >> poss[i];
	}

	for (int i = 0; i < q; i++) {
		int pos = poss[i];
		auto it = lower_bound(teachers.begin(), teachers.end(), pos);
		if (it == teachers.end()) {
			cout << n - *(it - 1) << '\n';
			continue;
		}

		if (it == teachers.begin()) {
			if (pos < *it)
				cout << *it - 1 << '\n';
			else
				cout << 0 << '\n';
			continue;
		}

		int left = *(it - 1);
		int right = *it;

		if (pos == left or pos == right) {
			cout << 0 << '\n';
			continue;
		}

		cout << (right - left) / 2 << endl;
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
