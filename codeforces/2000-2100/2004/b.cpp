//
// Created by 123 on 25-7-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int l1, l2, r1, r2;
	cin >> l1 >> r1 >> l2 >> r2;
	if (l1 > l2 || l1 == l2 && r1 > r2) {
		swap(l1, l2);
		swap(r1, r2);
	}
	if (r1 < l2) cout << "1\n"; //相互独立
	else if (l1 == l2 && r1 == r2) cout << r1 - l1 << endl; //区间相同
	else if (l1 == l2 && r1 != r2 || r1 == r2 and l1 != l2) cout << r1 - l2 + 1 << endl; //区间首相同或尾相同
	else if (l1 < l2 && r2 < r1) cout << r2 - l2 + 2 << endl; //相交
	else cout << r1 - l2 + 2 << endl; //其余包含的情况
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
