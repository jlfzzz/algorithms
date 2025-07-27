//
// Created by 123 on 25-7-27.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>> nums(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> nums[i][j];
		}
	}

	ranges::sort(nums, [](const auto& a, const auto& b) {
		return accumulate(a.begin(), a.end(), 0) > accumulate(b.begin(), b.end(), 0);
	});

	ll prev = 0;
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			prev += nums[i][j];
			ans += prev;
		}
	}
	cout << ans << '\n';
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