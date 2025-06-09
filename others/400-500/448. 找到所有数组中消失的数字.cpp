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
	const int mod = 998244353;
	vector<int> findDisappearedNumbers(vector<int>& nums) {
		int n = nums.size();
		for (auto& num : nums) {
			int x = (num - 1) % n;
			if (nums[x] <= n) {
				nums[x] += n;
			}
		}
		vector<int> ret;
		for (int i = 0; i < n; i++) {
			if (nums[i] <= n) {
				ret.push_back(i + 1);
			}
		}
		return ret;
	}
};