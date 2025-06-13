//
// Created by 123 on 25-6-11.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int maxDifference(string s, int k) {
		int n = s.size();
		int ans = INT_MIN;
		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 5; y++) {
				if (x == y) continue;
				vector<vector<int>> min_s(2, vector<int>(2, INT_MAX / 2));
				vector<int> cur_s(5);
				vector<int> pre_s(5);
				int left = 0;

				for (int i = 0; i < n; i++) {
					cur_s[s[i] - '0']++;
					int r = i + 1;
					while (r - left >= k && cur_s[x] > pre_s[x] && cur_s[y] > pre_s[y]) {
						min_s[pre_s[x] & 1][pre_s[y] & 1] = min(min_s[pre_s[x] & 1][pre_s[y] & 1], pre_s[x] - pre_s[y]);
						pre_s[s[left] - '0']++;
						left++;
					}

					ans = max(ans, cur_s[x] - cur_s[y] - min_s[cur_s[x] & 1 ^ 1][cur_s[y] & 1]);
				}
			}
		}
		return ans;
	}
};

class Solution {
public:
	int maxDifference(string s, int k) {
		constexpr int inf = INT_MAX / 2;
		int ans = -inf;

		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 5; y++) {
				if (x == y) {
					continue;
				}

				vector<int> cur_s(5);
				vector<int> pre_s(5);
				vector<vector<int> > min_s(2, vector<int>(2, inf));

				int left = 0;
				for (int i = 0; i < s.size(); i++) {
					cur_s[s[i] - '0']++;
					int r = i + 1;
					while (r - left >= k && cur_s[x] > pre_s[x] && cur_s[y] > pre_s[y]) {
						min_s[pre_s[x] & 1][pre_s[y] & 1] = min(min_s[pre_s[x] & 1][pre_s[y] & 1], pre_s[x] - pre_s[y]);
						pre_s[s[left] - '0']++;
						left++;
					}
					ans = max(ans, cur_s[x] - cur_s[y] - min_s[cur_s[x] & 1 ^ 1][cur_s[y] & 1]);
				}
			}
		}
		return ans;
	}
};
