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
	int maxHeight(vector<vector<int>> &cuboids) {
		for (auto &c : cuboids)
			sort(c.begin(), c.end());
		sort(cuboids.begin(), cuboids.end());
		int n = cuboids.size(), f[n];
		for (int i = 0; i < n; ++i) {
			f[i] = 0;
			for (int j = 0; j < i; ++j)
				// 排序后，cuboids[j][0] <= cuboids[i][0] 恒成立
					if (cuboids[j][1] <= cuboids[i][1] && cuboids[j][2] <= cuboids[i][2])
						f[i] = max(f[i], f[j]); // cuboids[j] 可以堆在 cuboids[i] 上
			f[i] += cuboids[i][2];
		}
		return *max_element(f, f + n);
	}
};
