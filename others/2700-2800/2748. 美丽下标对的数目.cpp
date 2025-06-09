//
// Created by 123 on 25-6-4.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int countBeautifulPairs(vector<int>& nums) {
		int ans = 0, cnt[10]{};
		for (int x : nums) {
			for (int y = 1; y < 10; y++) {
				if (cnt[y] && gcd(y, x % 10) == 1) {
					ans += cnt[y];
				}
			}
			while (x >= 10) {
				x /= 10;
			}
			cnt[x]++; // 统计最高位的出现次数
		}
		return ans;
	}
};