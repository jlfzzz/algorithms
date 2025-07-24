//
// Created by 123 on 25-6-4.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int longestValidSubstring(string word, vector<string> &forbidden) {
		unordered_set<string> all;
		for (const string &word: forbidden) {
			all.insert(word);
		}
		int ans = 0;
		int left = 0;
		int n = word.length();

		for (int right = 0; right < n; right++) {
			for (int i = right; i >= left && i > right - 10; --i) {
				if (all.contains(word.substr(i, right - i + 1))) {
					left = i + 1;
				}
			}
			ans = max(ans, right - left + 1);
		}
		return ans;
	}
};
