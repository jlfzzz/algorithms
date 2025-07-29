//
// Created by 123 on 25-7-29.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	string s;
	cin >> s;

	int n = s.length();
	cout << 1 << ' ' << n << ' ';

	// 找第一个'0'的位置
	int first_zero = -1;
	for (int i = 0; i < n; i++) {
		if (s[i] == '0') {
			first_zero = i;
			break;
		}
	}

	// 如果没有'0'，选择第一个字符与自己XOR
	if (first_zero == -1) {
		cout << 1 << ' ' << 1 << '\n';
		return;
	}

	string mx = s;
	int ans_l = 1; // 1-indexed
	int len = n - first_zero; // 后缀长度

	// 尝试所有可能的起始位置（长度为len的子串）
	for (int i = 0; i + len <= n; i++) {
		string t = s;

		// 将s[i...i+len-1]与s[n-len...n-1]进行XOR
		for (int j = 0; j < len; j++) {
			char original = s[n - len + j];
			char xor_with = s[i + j];
			t[n - len + j] = ((original - '0') ^ (xor_with - '0')) + '0';
		}

		if (t > mx) {
			mx = t;
			ans_l = i + 1; // 转换为1-indexed
		}
	}

	cout << ans_l << ' ' << ans_l + len - 1 << '\n';
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
