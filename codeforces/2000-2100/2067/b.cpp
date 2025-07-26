//
// Created by 123 on 25-7-26.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

constexpr int N = 1e4 + 5;
int arr[N];

void solve() {
	int n;
	cin >> n;
	int mx = 0;
	memset(arr, 0, sizeof(arr));
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		mx = max(mx, t);
		arr[t] += 1;
	}

	if (n % 2) {
		cout << "NO\n";
		return;
	}

	int prev = 0;
	for (int i = 1; i <= mx; i+= 1) {
		if (arr[i] == 0) {
			if (prev == 1) {
				cout << "NO\n";
				return;
			}
			prev = max(0, prev - 2);
			continue;
		}
		if (arr[i] == 1 && prev == 0) {
			cout << "NO\n";
			return;
		}
		prev = max(0, prev + arr[i] - 2);
	}
	if (prev % 2) {
		cout << "NO\n";
		return;
	}
	cout << "YES\n";
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