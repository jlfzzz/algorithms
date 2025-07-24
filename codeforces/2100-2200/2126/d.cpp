//
// Created by 123 on 25-7-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n, k;
	cin >> n >> k;
	vector<tuple<int, int, int> > arr(n);
	for (int i = 0; i < n; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		arr[i] = make_tuple(a, b, c);
	}
	sort(arr.begin(), arr.end(), [&](const auto &a, const auto &b) {
		if (get<0>(a) == get<0>(b)) {
			if (get<1>(a) == get<1>(b)) {
				return get<2>(a) < get<2>(b);
			} else {
				return get<1>(a) < get<1>(b);
			}
		}
		return get<0>(a) < get<0>(b);
	});

	for (int i = 0; i < n; i++) {
		auto &t = arr[i];
		if (get<0>(t) <= k and get<1>(t) >= k and get<2>(t) > k) {
			k = get<2>(t);
		}
	}
	cout << k << '\n';
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
