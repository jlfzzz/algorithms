//
// Created by 123 on 25-5-31.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int maxScoreSightseeingPair(vector<int>& values) {
		int ans = 0, mx = values[0]; // mx 表示 j 左边的 values[i] + i 的最大值
		for (int j = 1; j < values.size(); j++) {
			ans = max(ans, mx + values[j] - j);
			mx = max(mx, values[j] + j);
		}
		return ans;
	}
};