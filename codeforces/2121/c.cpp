//
// Created by 123 on 25-7-19.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// void solve() {
// 	int n, m;
// 	cin >> n >> m;
// 	vector<vector<int>> a(n, vector<int>(m));
// 	int mx = 0, cnt_mx = 0;
//
// 	// 输入 & 找最大值
// 	for (int i = 0; i < n; i++) {
// 		for (int j = 0; j < m; j++) {
// 			cin >> a[i][j];
// 			if (a[i][j] > mx) {
// 				mx = a[i][j];
// 				cnt_mx = 1;
// 			} else if (a[i][j] == mx) {
// 				cnt_mx++;
// 			}
// 		}
// 	}
//
// 	// 统计每行、每列有几个 mx
// 	vector<int> r(n), c(m);
// 	for (int i = 0; i < n; i++) {
// 		for (int j = 0; j < m; j++) {
// 			if (a[i][j] == mx) {
// 				r[i]++;
// 				c[j]++;
// 			}
// 		}
// 	}
//
// 	// 枚举所有交点，看是否能覆盖所有 mx
// 	bool ok = false;
// 	for (int i = 0; i < n && !ok; i++) {
// 		for (int j = 0; j < m && !ok; j++) {
// 			int cover = r[i] + c[j] - (a[i][j] == mx);
// 			if (cover == cnt_mx) {
// 				ok = true;
// 			}
// 		}
// 	}
//
// 	cout << (mx - (ok ? 1 : 0)) << '\n';
// }
//
//

void solve() {
	int n, m;
	cin >> n >> m;

	int mx = -1;
	vector<vector<int> > mat(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> mat[i][j];
			mx = max(mx, mat[i][j]);
		}
	}

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == mx) {
				cnt++;
			}
		}
	}

	vector r(n, 0);
	vector c(m, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == mx) {
				r[i] += 1;
				c[j] += 1;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (r[i] + c[j] - (mat[i][j] == mx) == cnt) {
				cout << mx - 1 << "\n";
				return;
			}
		}
	}
	cout << mx << "\n";
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
