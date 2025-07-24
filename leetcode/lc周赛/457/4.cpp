//
// Created by 123 on 25-7-6.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int minMoves(int sx, int sy, int tx, int ty) {
		if (sx == 0 and sy == 0) {
			if (tx > 0 || ty > 0) {
				return -1;
			}
			return 0;
		}

		auto dfs = [&](this auto&&dfs, int x, int y)->int {
			if (x < sx || y < sy) {
				return INT_MAX;
			}
			if (x == sx && y == sy) {
				return 0;
			}
			auto [mn, mx] = minmax(x, y);

		};

	}
};

