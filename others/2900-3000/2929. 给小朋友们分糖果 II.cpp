//
// Created by 123 on 25-6-1.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	long long distributeCandies(int n, int limit) {
		long long res = 0;
		for (int i = max(0, n - 2 * limit); i <= min(n, limit); i++) {
			res += min(limit, n - i) - max(0, n - i - limit) + 1;
		}
		return res;
	}
};