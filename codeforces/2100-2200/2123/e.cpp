//
// Created by 123 on 25-7-19.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

constexpr int N = 2e5 + 555;

// 差分数组
// 遍历到mex，当前freq[mex]的都要删，前面mex个至少保留mex个，所以diff[freq[mex]]++,diff[n-mex+1]--

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) { cin >> a[i]; }

	int max_val = *ranges::max_element(a);
	vector<int> freq(max_val + 2, 0);
	for (int x: a) {
		freq[x]++;
	}

	int first = max_val + 1; // 默认MEX
	for (int i = 0; i <= max_val + 1; i++) {
		if (freq[i] == 0) {
			first = i;
			break;
		}
	}

	vector<int> diff(n + 2, 0);
	for (int i = first; i >= 0; i--) {
		int fre = freq[i];
		diff[fre]++;
		diff[n - i + 1]--;
	}

	cout << diff[0] << ' ';
	for (int i = 1; i <= n; i++) {
		diff[i] += diff[i - 1];
		cout << diff[i] << ' ';
	}
	cout << '\n';
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
