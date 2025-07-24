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
	int maxDifference(string s) {
		int cnt[26]{};
		for (char b : s) {
			cnt[b - 'a']++;
		}

		int max1 = 0, min0 = INT_MAX;
		for (int c : cnt) {
			if (c % 2) {
				max1 = max(max1, c);
			} else if (c) {
				min0 = min(min0, c);
			}
		}
		return max1 - min0;
	}
};