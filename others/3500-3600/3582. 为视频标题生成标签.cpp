//
// Created by 123 on 25-6-15.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	string generateTag(string caption) {
		string ans = "#";
		bool new_word = true;

		for (int i = 0; i < caption.size(); i++) {
			char c = caption[i];
			if (isalpha(c)) {
				if (new_word) {
					ans += toupper(c);
					new_word = false;
				} else {
					ans += tolower(c);
				}
			} else {
				new_word = true;
			}
		}

		if (ans.size() > 1) {
			ans[1] = tolower(ans[1]);
		}
		return ans.substr(0, min(100, (int)ans.size()));
	}
};