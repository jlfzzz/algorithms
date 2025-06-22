//
// Created by 123 on 25-6-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

const int MX = 101;
bool np[MX];

auto init = [] {
	np[1] = true;
	for (int i = 2; i * i < MX; i++) {
		if (!np[i]) {
			for (int j = i * i; j < MX; j += i) {
				np[j] = true; // j 是质数 i 的倍数
			}
		}
	}
	return 0;
	}();

class Solution {
public:
	bool checkPrimeFrequency(vector<int> &nums) {
		unordered_map<int, int> cnt;
		for (int x : nums) {
			cnt[x]++;
		}
		for (auto &[_, c] : cnt) {
			if (!np[c]) {
				return true;
			}
		}
		return false;
	}
};

class Solution {
public:
	bool checkPrimeFrequency(vector<int>& nums) {
		unordered_map<int, int> mp;
		for (int x : nums) {
			mp[x]++;
		}

		for (auto& p : mp) {
			if (p.second != 1) {
				int cnt = 1;
				for (int i = 2; i < p.second; i++) {
					if (p.second % i == 0) cnt++;
				}
				if (cnt == 1) {
					return true;
				}
			}
		}
		return false;
	}
};
