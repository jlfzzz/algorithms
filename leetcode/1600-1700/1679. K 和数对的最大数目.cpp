//
// Created by 123 on 25-5-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  int maxOperations(vector<int>& nums, int k) {
    ranges::sort(nums);
    int l = 0;
    int r = nums.size() - 1;
    int ans = 0;
    while (l < r) {
      int left = nums[l];
      int right = nums[r];
      while (l < r && left + right < k) {
        l++;
        left = nums[l];
      }
      while (l < r && left + right > k) {
        r--;
        right = nums[r];
      }
      if (l != r && left + right == k) {
        ans++;
        l++;
        r--;
      }
    }
    return ans;
  }
};