//
// Created by 123 on 25-6-5.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
	// 2271. 毯子覆盖的最多白色砖块数
	long long maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
		long long ans = 0, cover = 0;
		int left = 0;
		for (auto& tile : tiles) {
			int tl = tile[0], tr = tile[1], c = tile[2];
			cover += (long long) (tr - tl + 1) * c;
			while (tiles[left][1] + carpetLen - 1 < tr) {
				cover -= (long long) (tiles[left][1] - tiles[left][0] + 1) * tiles[left][2];
				left++;
			}
			long long uncover = max((long long) (tr - carpetLen + 1 - tiles[left][0]) * tiles[left][2], 0LL);
			ans = max(ans, cover - uncover);
		}
		return ans;
	}

public:
	long long maximumCoins(vector<vector<int>>& coins, int k) {
		ranges::sort(coins, {}, [](auto& c) { return c[0]; });
		long long ans = maximumWhiteTiles(coins, k);

		ranges::reverse(coins);
		for (auto& t : coins) {
			int tmp = t[0];
			t[0] = -t[1];
			t[1] = -tmp;
		}
		return max(ans, maximumWhiteTiles(coins, k));
	}
};
