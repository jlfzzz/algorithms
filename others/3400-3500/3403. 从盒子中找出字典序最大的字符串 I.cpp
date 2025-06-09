//
// Created by 123 on 25-6-4.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	string lastSubstring(string s) {
		int i = 0, j = 1, n = s.size();
		while (j < n) {
			int k = 0;
			while (j + k < n && s[i + k] == s[j + k]) {
				k++;
			}
			if (j + k < n && s[i + k] < s[j + k]) {
				int t = i;
				i = j;
				j = max(j + 1, t + k + 1);
			} else {
				j = j + k + 1;
			}
		}
		return s.substr(i, n - i);
	}

	string answerString(string word, int numFriends) {
		if (numFriends == 1) {
			return word;
		}
		string last = lastSubstring(word);
		int n = word.size(), m = last.size();
		return last.substr(0, min(m, n - numFriends + 1));
	}
};

class Solution {
public:
	string answerString(string s, int k) {
		if (k == 1) {
			return s;
		}
		int n = s.size();
		string ans;
		for (int i = 0; i < n; i++) {
			ans = max(ans, s.substr(i, n - max(k - 1, i)));
		}
		return ans;
	}
};

