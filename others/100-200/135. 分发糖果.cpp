//
// Created by 123 on 25-6-2.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int candy(vector<int>& ratings) {
		int n = ratings.size();
		vector<int> candies(n, 1);

		// 从左往右
		for (int i = 1; i < n; ++i) {
			if (ratings[i] > ratings[i - 1]) {
				candies[i] = candies[i - 1] + 1;
			}
		}

		// 从右往左
		for (int i = n - 2; i >= 0; --i) {
			if (ratings[i] > ratings[i + 1]) {
				candies[i] = max(candies[i], candies[i + 1] + 1);
			}
		}

		// 求和
		int total = accumulate(candies.begin(), candies.end(), 0);
		return total;
	}
};
