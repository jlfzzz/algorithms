//
// Created by 123 on 25-6-9.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	string longestNiceSubstring(string s) {
		int n = s.size();
		int ansl = 0;
		int ansr = 0;

		auto helper = [&](this auto&&helper, int l, int r) -> void {
			if (l == r) return;

			unordered_set<char> set;
			for (int i = l; i < r; i++) {
				set.insert(s[i]);
			}

			for (int i = l; i < r; i++) {
				char c = s[i];
				if (!set.contains(c ^ 32)) {
					helper(l, i);
					helper(i + 1, r);
					return;
				}
			}

			if (r - l > ansr - ansl) {
				ansr = r;
				ansl = l;
			}
		};
		helper(0, n);
		return s.substr(ansl, ansr - ansl);
	}
};

class Solution {
public:
	string longestNiceSubstring(string s) {
		int n = s.size();
		string ans = "";

		for (int i = 0; i < n; ++i) {
			unordered_set<char> chars;
			for (int j = i; j < n; ++j) {
				chars.insert(s[j]);
				if (isNice(chars)) {
					if (j - i + 1 > ans.size()) {
						ans = s.substr(i, j - i + 1);
					}
				}
			}
		}

		return ans;
	}

	bool isNice(const unordered_set<char>& chars) {
		for (char c : chars) {
			if (isalpha(c)) {
				if (chars.count(tolower(c)) == 0 || chars.count(toupper(c)) == 0) {
					return false;
				}
			}
		}
		return true;
	}
};
