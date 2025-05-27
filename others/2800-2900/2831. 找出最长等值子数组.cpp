//
// Created by 123 on 25-5-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  int longestEqualSubarray(vector<int>& nums, int k) {
    unordered_map<int, vector<int>> record;
    int n = nums.size();
    if (n == 0) return 0;
    for (int i = 0; i < n; i++) {
      record[nums[i]].push_back(i);
    }

    int ans = 1;
    for (auto it = record.begin(); it != record.end(); ++it) {
      int m = it->second.size();
      auto& v = it->second;
      int left = 0;
      int used = 0;
      for (int i = 1; i < m; i++) {
        used += v[i] - v[i - 1] - 1;
        while (used > k) {
          used -= v[left + 1] - v[left] - 1;
          left++;
        }
        ans = max(ans, i - left + 1);
      }
    }
    return ans;
  }
};

class Solution2 {
public:
  int longestEqualSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    int ans = 0;
    unordered_map<int, int> cnt;
    for (int i = 0, j = 0; j < n; j++) {
      cnt[nums[j]]++;
      /*当前区间中，无法以 nums[i] 为等值元素构成合法等值数组*/
      while (j - i + 1 - cnt[nums[i]] > k) {
        cnt[nums[i]]--;
        i++;
      }
      ans = max(ans, cnt[nums[j]]);
    }
    return ans;
  }
};