#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int maxFrequencyScore(vector<int> &nums, long long k) {
		int n = nums.size();
		ranges::sort(nums);

		int left = 0;
		ll ans = 0;
		vector<ll> prefix_sum(n + 1);
		for (int i = 0; i < n; i++) {
			prefix_sum[i + 1] = prefix_sum[i] + nums[i];
		}

		auto check = [&](int l, int r, int mid) -> bool {
			ll left_half = 1LL * nums[mid] * (mid - l) - (prefix_sum[mid] - prefix_sum[l]);
			ll right_half = prefix_sum[r + 1] - prefix_sum[mid] - 1LL * nums[mid] * (r - mid + 1);
			return left_half + right_half <= k;
		};

		for (int right = 0; right < n; right++) {
			while (!check(left, right, (left + right) / 2)) {
				left++;
			}

			ans = max(ans, 1LL * right - left + 1LL);
		}
		return ans;
	}
};


class Solution {
public:
	int maxFrequencyScore(vector<int> &nums, long long k) {
		sort(nums.begin(), nums.end());

		int n = nums.size();
		vector<long long> s(n + 1, 0);
		for (int i = 0; i < n; i++) {
			s[i + 1] = s[i] + nums[i];
		}

		// 把 nums[l] 到 nums[r] 都变成 nums[i]
		auto distance_sum = [&](int l, int i, int r) -> long long {
			long long left = (long long) nums[i] * (i - l) - (s[i] - s[l]);
			long long right = s[r + 1] - s[i + 1] - (long long) nums[i] * (r - i);
			return left + right;
		};

		int ans = 0, left = 0;
		for (int i = 0; i < n; i++) {
			while (distance_sum(left, (left + i) / 2, i) > k) {
				left++;
			}
			ans = max(ans, i - left + 1);
		}
		return ans;
	}
};
