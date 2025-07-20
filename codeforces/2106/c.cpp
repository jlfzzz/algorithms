//
// Created by 123 on 25-7-20.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	vector<int> b(n);
	for (int i = 0; i < n; i++) cin >> b[i];

	bool flag = true;
	int target = -1;
	for (int i = 0; i < n; i++) {
		int x = a[i];
		int y = b[i];
		if (y != -1) {
			flag = false;
			if (target == -1) {
				target =  x + y;
			} else {
				if (x + y != target) {
					cout << 0 << '\n';
					return;
				}
			}
		}
	}
	int mn = ranges::min(a);
	int mx = ranges::max(a);
	if (!flag) {
		if (mx > target or target - mn > k) {
			cout << 0 << '\n';
			return;
		}
		cout << 1 << '\n';
		return;
	}


	cout << max(0, mn + k - mx + 1) << '\n';
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