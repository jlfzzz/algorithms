//
// Created by 123 on 25-7-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

// 排序，最小的必选，然后第二个选不是第一个的倍数的第一个数，然后枚举判断

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	ranges::sort(a);
	int x = a[0];
	int y = -1;
	int j = 1;
	while (j < n) {
		if (a[j] % x) {
			y = a[j];
			break;
		}
		j++;
	}
	if (y == -1) {
		cout << "YES\n";
		return;
	}
	for (int i = 2; i < n; i++) {
		if (a[i] % x and a[i] % y) {
			cout << "NO\n";
			return;
		}
	}
	cout << "YES\n";
	// int g = gcd(a[0], a[1]);
	// for (int i = 2; i < n; i++) {
	// 	g = gcd(a[i], a[i - 1]);
	// }
	//
	// for (int x : a) {
	// 	if (x == g) {
	// 		cout << "YES" << endl;
	// 		return;
	// 	}
	// }
	// cout << "NO" << endl;
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
