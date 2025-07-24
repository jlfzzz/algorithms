//
// Created by 123 on 25-7-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	string s;
	cin >> s;
	// string s = "()()";
	int n = s.length();
	vector<tuple<int, int, char> > arr(n);
	int pre = 0;
	for (int i = 0; i < n; i++) {
		char c = s[i];
		arr[i] = make_tuple(pre, i, c);
		if (c == '(') {
			pre++;
		} else {
			pre--;
		}
		// cout << pre << endl;
	}

	sort(arr.begin(), arr.end(), [&](const auto &a, const auto &b) {
		if (get<0>(a) == get<0>(b)) {
			return get<1>(a) > get<1>(b);
		}
		return get<0>(a) < get<0>(b);
	});
	for (int i = 0; i < n; i++) {
		cout << get<2>(arr[i]);
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	solve();
}
