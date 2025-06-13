//
// Created by 123 on 25-6-10.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int countPairs(vector<int>& nums) {
		int ans = 0;
		ranges::sort(nums);
		unordered_map<int, int> cnt;
		for (int x : nums) {
			unordered_set<int> st = {x};
			string s = to_string(x);
			int m = s.size();
			for (int i = 0; i < m; i++) {
				for (int j = i + 1; j < m; j++) {
					swap(s[i], s[j]);
					st.insert(stoi(s));
					for (int k = 0; k < m; k++) {
						for (int l = k + 1; l < m; l++) {
							swap(s[k], s[l]);
							st.insert(stoi(s));
							swap(s[k], s[l]);
						}
					}
					swap(s[i], s[j]);
				}
			}

			for (int v : st) {
				ans += cnt.contains(v) ? cnt[v] : 0;
			}
			cnt[x]++;
		}
		return ans;
	}
};