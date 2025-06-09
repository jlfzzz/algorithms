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
	int maximizeWin(vector<int>& prizePositions, int k) {
		int n = prizePositions.size();
		vector<int> dp(n + 1);
		int left = 0;
		int ans = 0;
		for (int right = 0; right < n; right++) {
			while (prizePositions[right] - prizePositions[left] > k) {
				left++;
			}
			ans = max(ans, right - left + 1 + dp[left]);
			dp[right + 1] = max(dp[right], right - left + 1);
		}
		return ans;
	}
};

class Solution {
public:
	int maximizeWin(vector<int>& prizePositions, int k) {
		int n = prizePositions.size();
		vector<int> dp(n + 1);
		int ans = 0;
		for (int left = 0, right = 0; right < n; right++) {
			while (prizePositions[right] - prizePositions[left] > k) {
				left++;
			}
			ans = max(ans, right - left + 1 + dp[left]);
			dp[right + 1] = max(dp[right], right - left + 1);
		}
		return ans;
	}
};