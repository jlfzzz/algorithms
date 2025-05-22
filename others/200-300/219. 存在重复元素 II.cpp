//
// Created by 123 on 25-5-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> mp;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      if (mp.find(nums[i]) == mp.end()) {
        mp[nums[i]] = i;
      } else {
        if (i - mp[nums[i]] <= k) {
          return true;
        }
        mp[nums[i]] = i;
      }
    }
    return false;
  }
};