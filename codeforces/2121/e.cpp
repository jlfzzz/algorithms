#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 上下界数位dp
// 还有贪心做法，更简单应该

void solve() {
	int l, r;
	cin >> l >> r;

	string s1 = to_string(l);
	string s2 = to_string(r);
	int n = s1.length();

	vector<vector<vector<int> > > memo(n + 1, vector<vector<int> >(2, vector<int>(2, -1)));

	auto dfs = [&](this auto &&dfs, int i, bool is_lo, bool is_hi) -> int {
		if (i == n) return 0;

		int &res = memo[i][is_lo][is_hi];
		if (!is_lo and !is_hi and res != -1) return res;

		int t = INT_MAX;
		int x1 = s1[i] - '0';
		int x2 = s2[i] - '0';
		int lo = 0;
		int hi = 9;
		if (i == 0) lo = 1;

		if (is_lo) lo = x1;
		if (is_hi) hi = x2;

		for (int j = lo; j <= hi; j++) {
			int extra = 0;
			if (j == x1) extra++;
			if (j == x2) extra++;
			t = min(t, dfs(i + 1, is_lo and j == lo, is_hi and j == hi) + extra);
		}
		res = t;
		return res;
	};
	cout << dfs(0, true, true) << '\n';
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
