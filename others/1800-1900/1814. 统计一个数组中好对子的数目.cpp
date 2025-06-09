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
	int countNicePairs(vector<int>& nums) {
		const int MOD = 1000000007;
		int res = 0;
		unordered_map<int, int> h;
		for (int i : nums) {
			int temp = i, j = 0;
			while (temp > 0) {
				j = j * 10 + temp % 10;
				temp /= 10;
			}
			res = (res + h[i - j]) % MOD;
			h[i - j]++;
		}
		return res;
	}
};