//
// Created by 123 on 25-6-6.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int countQuadruplets(vector<int>& nums) {
		int n = nums.size();
		unordered_map<int, int> cnt;
		int ans = 0;
		for (int b = n - 3; b >= 1; --b) {
			int c = b + 1;
			for (int d = c + 1; d < n; ++d) {
				cnt[nums[d] - nums[c]]++;
			}
			for (int a = 0; a < b; ++a) {
				ans += cnt[nums[a] + nums[b]];
			}
		}
		return ans;
	}
};

class Solution {
public:
	int countQuadruplets(vector<int>& nums) {
		int n = nums.size();
		int ans = 0;

		for (int i = 0; i < n - 3; i++) {
			for (int j = i + 1; j < n - 2; j++) {
				unordered_map<int, int> map;
				map[nums[n - 1]]++;
				for (int k = n - 2; k > j; k--) {
					ans += map[nums[i] + nums[j] + nums[k]];
					map[nums[k]]++;
				}
			}
		}
		return ans;
	}
};

class Solution {
public:
	int countQuadruplets(vector<int>& nums) {
		int n = nums.size();
		int ans = 0;
		for (int a = 0; a < n; ++a) {
			for (int b = a + 1; b < n; ++b) {
				for (int c = b + 1; c < n; ++c) {
					for (int d = c + 1; d < n; ++d) {
						if (nums[a] + nums[b] + nums[c] == nums[d]) {
							++ans;
						}
					}
				}
			}
		}
		return ans;
	}
};