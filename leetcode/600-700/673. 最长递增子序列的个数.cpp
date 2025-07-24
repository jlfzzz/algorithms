#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>
#include <memory>
#include <map>

using namespace std;


class Solution {
public:
	int findNumberOfLIS(vector<int>& nums) {
		int n = nums.size();
		vector<pair<int,int>> dp(n);
		int max_len = 0;
		for (int i = 0; i < n; i++) {
			dp[i].first = 1;
			dp[i].second = 1;
			for (int j = i; j >= 0; j--) {
				if (nums[j] < nums[i]) {
					if (dp[j].first + 1 > dp[i].first) {
						dp[i].first = dp[j].first + 1;
						dp[i].second = dp[j].second;
					} else if (dp[j].first + 1 == dp[i].first) {
						dp[i].second += dp[j].second;
					}
				}
			}
			max_len = max(max_len, dp[i].first);
		}

		int ans = 0;
		for (int i = 0; i < n; i++) {
			if (dp[i].first == max_len) {
				ans += dp[i].second;
			}
		}
		return ans;
	}
};


class Solution {
public:
	int findNumberOfLIS(vector<int> &nums) {
		int n = nums.size(), maxLen = 0, ans = 0;
		vector<int> dp(n), cnt(n);
		for (int i = 0; i < n; ++i) {
			dp[i] = 1;
			cnt[i] = 1;
			for (int j = 0; j < i; ++j) {
				if (nums[i] > nums[j]) {
					if (dp[j] + 1 > dp[i]) {
						dp[i] = dp[j] + 1;
						cnt[i] = cnt[j]; // 重置计数
					} else if (dp[j] + 1 == dp[i]) {
						cnt[i] += cnt[j];
					}
				}
			}
			if (dp[i] > maxLen) {
				maxLen = dp[i];
				ans = cnt[i]; // 重置计数
			} else if (dp[i] == maxLen) {
				ans += cnt[i];
			}
		}
		return ans;
	}
};


class Solution {
public:
	int findNumberOfLIS(vector<int> &nums) {
		int n = nums.size();
		vector<pair<int, int> > dp(n, {1, 1});
		int mxLen = 1;

		for (int i = 0; i < n; i++) {
			int x = nums[i];

			for (int j = 0; j < i; j++) {
				if (nums[j] < nums[i]) {
					int before = dp[j].first + 1;

					if (before > dp[i].first) {
						dp[i].first = before;
						dp[i].second = dp[j].second;
					} else if (before == dp[i].first) {
						dp[i].second += dp[j].second;
					}

					mxLen = max(mxLen, dp[i].first);
				}
			}
		}

		int ans = 0;
		for (auto &p: dp) {
			if (p.first == mxLen) {
				ans += p.second;
			}
		}
		return ans;
	}
};
