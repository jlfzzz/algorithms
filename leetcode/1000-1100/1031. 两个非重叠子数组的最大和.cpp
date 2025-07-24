//
// Created by 123 on 25-6-4.
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
class Solution {
public:
	int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
		return max(helper(nums, firstLen, secondLen),
				   helper(nums, secondLen, firstLen));
	}

	int helper(vector<int>& nums, int L, int M) {
		int n = nums.size();
		vector<int> prefix(n + 1, 0); // prefix sum
		for (int i = 0; i < n; ++i) {
			prefix[i + 1] = prefix[i] + nums[i];
		}

		int maxL = 0, ans = 0;
		for (int i = L + M; i <= n; ++i) {
			maxL = max(maxL, prefix[i - M] - prefix[i - M - L]); // max sum of L before M
			ans = max(ans, maxL + prefix[i] - prefix[i - M]); // L + M
		}
		return ans;
	}
};


class Solution {
public:
	int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
		return max(getMax(nums, firstLen, secondLen), getMax(nums, secondLen, firstLen));
	}

	int getMax(vector<int>& nums, int len1, int len2) {
		int n = nums.size();
		vector<int> dp1(n), dp2(n);

		// dp1[i]: max sum of len1 ending at or before i
		int s = 0;
		for (int i = 0; i < len1; ++i) s += nums[i];
		dp1[len1 - 1] = s;
		for (int i = len1; i < n; ++i) {
			s += nums[i] - nums[i - len1];
			dp1[i] = max(dp1[i - 1], s);
		}

		// dp2[i]: max sum of len1 starting at or after i
		s = 0;
		for (int i = n - 1; i > n - len1 - 1; --i) s += nums[i];
		dp2[n - len1] = s;
		for (int i = n - len1 - 1; i >= 0; --i) {
			s += nums[i] - nums[i + len1];
			dp2[i] = max(dp2[i + 1], s);
		}

		// Slide a window of len2 and try combining with dp1 or dp2
		s = 0;
		for (int i = 0; i < len2; ++i) s += nums[i];
		int ans = 0;
		for (int i = len2; i < n; ++i) {
			s += nums[i] - nums[i - len2];
			int left = (i - len2 >= 0) ? dp1[i - len2] : 0;
			int right = (i + 1 < n) ? dp2[i + 1] : 0;
			ans = max(ans, s + max(left, right));
		}

		return ans;
	}
};



