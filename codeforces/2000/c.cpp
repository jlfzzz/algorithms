//
// Created by 123 on 25-7-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	int m;
	cin >> m;
	while (m--) {
		string s;
		cin >> s;
		int l = s.length();
		if (l != n) {
			cout << "NO\n";
			continue;
		}

		// 建立双向映射关系
		unordered_map<int, char> num_to_char;    // 数字 -> 字符
		unordered_map<char, int> char_to_num;    // 字符 -> 数字

		bool flag = true;
		for (int i = 0; i < n; i++) {
			int num = a[i];
			char ch = s[i];

			// 检查数字到字符的映射是否一致
			if (num_to_char.count(num) && num_to_char[num] != ch) {
				flag = false;
				break;
			}

			// 检查字符到数字的映射是否一致
			if (char_to_num.count(ch) && char_to_num[ch] != num) {
				flag = false;
				break;
			}

			// 建立/更新映射关系
			num_to_char[num] = ch;
			char_to_num[ch] = num;
		}

		cout << (flag ? "YES" : "NO") << "\n";
	}
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