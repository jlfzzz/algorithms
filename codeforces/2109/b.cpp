//
// Created by 123 on 25-7-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, m, x, y;
	cin >> n >> m >> x >> y;

	// 特殊处理第一步。其他的就是ceil(log2(x))
	vector<pair<int, int> > four_cases = {{x, m}, {n - x + 1, m}, {n, y}, {n, m - y + 1}};

	int ans = INT_MAX;
	for (auto &[p1, p2]: four_cases) {
		ans = min(ans, (int) (ceil(log2(p1)) + ceil(log2(p2))) + 1);
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
