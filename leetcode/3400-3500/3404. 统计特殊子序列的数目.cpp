//
// Created by 123 on 25-6-8.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	using ll = long long;
	ll numberOfSubsequences(vector<int>& nums) {
		int n = nums.size();
		ll ans = 0;

		// 用 pair<int, int> 表示 ratio (约分后的分数)
		map<pair<int, int>, int> mp;

		for (int b = n - 3; b >= 1; --b) {
			int c = b + 2;
			for (int d = c + 2; d < n; ++d) {
				int num = nums[d], den = nums[c];
				int g = gcd(num, den);
				num /= g;
				den /= g;
				mp[{num, den}] += 1;
			}

			for (int a = 0; a < b - 1; ++a) {
				int num = nums[a], den = nums[b];
				int g = gcd(num, den);
				num /= g;
				den /= g;
				ans += mp[{num, den}];
			}
		}

		return ans;
	}
};

class Solution {
public:
	long long numberOfSubsequences(vector<int>& nums) {
		int n = nums.size();
		unordered_map<int, int> suf;
		// 枚举 c
		for (int i = 4; i < n - 2; i++) {
			int c = nums[i];
			// 枚举 d
			for (int j = i + 2; j < n; j++) {
				int d = nums[j];
				int g = gcd(c, d);
				// 把分子和分母（两个 short）压缩成一个 int
				suf[(d / g) << 16 | (c / g)]++;
			}
		}

		long long ans = 0;
		// 枚举 b
		for (int i = 2; i < n - 4; i++) {
			int b = nums[i];
			// 枚举 a
			for (int j = 0; j < i - 1; j++) {
				int a = nums[j];
				int g = gcd(a, b);
				ans += suf[(a / g) << 16 | (b / g)];
			}
			// 撤销之前统计的 d'/c'
			int c = nums[i + 2];
			for (int j = i + 4; j < n; j++) {
				int d = nums[j];
				int g = gcd(c, d);
				suf[(d / g) << 16 | (c / g)]--;
			}
		}
		return ans;
	}
};