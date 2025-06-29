//
// Created by 123 on 25-6-29.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	vector<int> longestCommonPrefix(vector<string>& words) {
		int n = words.size();
		if (n == 1) return {0};

		vector<int> diff(n - 1);
		auto count = [](const string &a, const string &b) -> int {
			int i = 0;
			while (i < a.size() && i < b.size() && a[i] == b[i]) {
				++i;
			}
			return i;
		};

		for (int i = 0; i < n - 1; ++i) {
			diff[i] = count(words[i], words[i + 1]);
		}

		vector<int> pre(n - 1), suf(n - 1);
		pre[0] = diff[0];
		for (int i = 1; i < n - 1; ++i) {
			pre[i] = max(pre[i - 1], diff[i]);
		}

		suf[n - 2] = diff[n - 2];
		for (int i = n - 3; i >= 0; --i) {
			suf[i] = max(suf[i + 1], diff[i]);
		}

		vector<int> ans(n);
		ans[0] = (n >= 3 ? suf[1] : 0);
		ans[n - 1] = (n >= 3 ? pre[n - 3] : 0);

		for (int i = 1; i < n - 1; ++i) {
			int t = count(words[i - 1], words[i + 1]);
			int l = (i >= 2 ? pre[i - 2] : 0);
			int r = (i + 1 < n - 1 ? suf[i + 1] : 0);
			ans[i] = max({t, l, r});
		}

		return ans;
	}
};
