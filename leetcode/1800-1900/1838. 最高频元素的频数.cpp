//
// Created by 123 on 25-5-21.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  int maxFrequency(vector<int>& nums, int k) {
    int n = nums.size();
    int ans = 0;
    int use = 0;
    ranges::sort(nums, greater<>());
    int left = 0;
    ll prefix_sum = 0;
    for (int right = 0; right < n; right++) {
      prefix_sum += nums[right];
      while (1LL * nums[left] * (right - left + 1) - prefix_sum > k * 1LL) {
        prefix_sum -= nums[left];
        left++;
      }
      ans = max(ans, right - left + 1);
    }
    return ans;
  }
};