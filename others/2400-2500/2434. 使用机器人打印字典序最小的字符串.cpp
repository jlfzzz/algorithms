//
// Created by 123 on 25-6-6.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	string robotWithString(string s) {
		int n = s.size();
		vector<int> suf(n + 1);
		suf[n] = 10000;

		for (int i = n - 1; i >= 0; i--) {
			char c = s[i];
			suf[i] = min(c - 'a', suf[i + 1]);
		}

		stack<int> st;
		string ans;
		for (int i = 0; i < n; i++) {
			st.emplace(s[i] - 'a');
			while (!st.empty() && st.top() <= suf[i + 1]) {
				const auto x = st.top();
				st.pop();
				ans += x + 'a';
			}
		}
		return ans;
	}
};
