//
// Created by 123 on 25-6-8.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int longestSubstring(string s, int k) {
		int n = s.size();
		if (n == 0) return 0;

		unordered_map<char, int> mp;
		for (char c: s) {
			mp[c]++;
		}

		for (int i = 0; i < n; i++) {
			if (mp[s[i]] < k) {
				int j = i + 1;
				while (j < n && mp[s[j]] < k) {
					++j;
				}
				return max(longestSubstring(s.substr(0, i), k), longestSubstring(s.substr(j), k));
			}
		}
		return n;
	}
};


class Solution {
public:
	int longestSubstring(string s, int k) {
		return dfs(s, k);
	}

	int dfs(const string &s, int k) {
		int n = s.size();
		if (n == 0) return 0;

		unordered_map<char, int> freq;
		for (char c: s) {
			freq[c]++;
		}

		// 找到第一个小于 k 的字符，作为分割点
		for (int i = 0; i < n; ++i) {
			if (freq[s[i]] < k) {
				int j = i + 1;
				while (j < n && freq[s[j]] < k) ++j;

				// 分别对左右两段递归
				return max(dfs(s.substr(0, i), k), dfs(s.substr(j), k));
			}
		}

		// 所有字符都满足出现次数 >= k
		return n;
	}
};


class Solution {
public:
	int longestSubstring(string s, int k) {
		if (s.size() < k)
			return 0;
		unordered_set<char> chars(s.begin(), s.end());
		unordered_map<char, int> counter;
		for (char c: s)
			counter[c]++;
		for (char c: chars) {
			vector<string> t;
			if (counter[c] < k) {
				split(s, t, c);
				int res = 0;
				for (string tn: t) {
					res = max(res, longestSubstring(tn, k));
				}
				return res;
			}
		}
		return s.size();
	}

	void split(const string &s, vector<string> &sv, const char flag = ' ') {
		sv.clear();
		istringstream iss(s);
		string temp;

		while (getline(iss, temp, flag)) {
			sv.push_back(temp);
		}
	}
};

class Solution {
public:
	int longestSubstring(string s, int k) {
		int n = s.size(), ans = 0;
		for (int m = 1; m <= 26 && m * k <= n; m++) {
			unordered_map<char, int> cnt;
			int left = 0, cnt_k = 0;
			for (int right = 0; right < n; right++) {
				if (++cnt[s[right]] == k) {
					cnt_k++;
				}
				while (cnt.size() > m) {
					if (cnt[s[left]] == k) {
						cnt_k--;
					}
					if (--cnt[s[left]] == 0) {
						cnt.erase(s[left]);
					}
					left++;
				}
				if (cnt_k == m) {
					ans = max(ans, right - left + 1);
				}
			}
		}
		return ans;
	}
};
