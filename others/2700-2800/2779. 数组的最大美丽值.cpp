//
// Created by 123 on 25-5-20.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  int maximumBeauty(vector<int>& nums, int k) {
    ranges::sort(nums);
    int ans = 0, left = 0;
    for (int right = 0; right < nums.size(); right++) {
      while (nums[right] - nums[left] > k * 2) {
        left++;
      }
      ans = max(ans, right - left + 1);
    }
    return ans;
  }
};