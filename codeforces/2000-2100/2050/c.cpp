//
// Created by 123 on 25-7-29.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	string s;
	cin >> s;

	int cnt2 = 0;
	int cnt3 = 0;
	ll total = 0;

	for (char c: s) {
		if (c == '2') {
			cnt2++;
		} else if (c == '3') {
			cnt3++;
		}
		total += c - '0';
	}

	if (total % 9 == 0) {
		cout << "YES\n";
		return;
	}

	bool Flag = false;
	for (int i = 0; i <= min(cnt2, 9); i++) {
		//lcm(2,9)=18,18/2=9,所以最多操作9次
		for (int j = 0; j <= min(cnt3, 3); j++) {
			//lcm(3,9)=9,9/3=3,所以最多操作3次
			if ((total + 2 * i + 6 * j) % 9 == 0) {
				//判断是否为9的倍数
				Flag = true;
			}
		}
	}
	if (Flag) cout << "YES\n";
	else cout << "NO\n";
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
