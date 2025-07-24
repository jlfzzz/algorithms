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
	vector<string> partitionString(string s) {
		int n = s.size();
		unordered_set<string> set;
		string path = "";
		vector<string> res;
		for (int i = 0; i < n; i++) {
			path += s[i];
			if (!set.contains(path)) {
				set.insert(path);
				res.push_back(path);
				path.clear();
			}
		}
		return res;
	}
};