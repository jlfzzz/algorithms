//
// Created by 123 on 25-7-25.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

int n, tmp;

void solve() {
	cin >> n;
	cout << "digit" << endl;
	cin >> tmp;
	cout << "digit" << endl;
	cin >> tmp;
	cout << "add -8" << endl;
	cin >> tmp;
	cout << "add -4" << endl;
	cin >> tmp;
	cout << "add -2" << endl;
	cin >> tmp;
	cout << "add -1" << endl;
	cin >> tmp;
	cout << "mul " << n << endl;
	cin >> tmp;
	cout << "!" << endl;
	cin >> tmp;
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
