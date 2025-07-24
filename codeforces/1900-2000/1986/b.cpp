//
// Created by 123 on 25-7-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> g[i][j];
		}
	}

	auto ok = [&](int i, int j) {
		return i >= 0 && i < n && j >= 0 && j < m;
	};

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int left = ok(i - 1, j) ? g[i - 1][j] : INT_MIN;
			int right = ok(i + 1, j) ? g[i + 1][j] : INT_MIN;
			int up = ok(i, j - 1) ? g[i][j - 1] : INT_MIN;
			int down = ok(i, j + 1) ? g[i][j + 1] : INT_MIN;
			int x = g[i][j];
			int mx = max({left, right, up, down});
			if (x > mx) {
				g[i][j] = mx;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << g[i][j] << " ";
		}
		cout << '\n';
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
