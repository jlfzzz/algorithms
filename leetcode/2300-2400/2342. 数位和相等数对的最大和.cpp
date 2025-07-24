//
// Created by 123 on 25-5-20.
//
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
  int maximumSum(vector<int>& nums) {
    vector<int> v(100, -1);
    int ans = -1;
    for (int i = 0; i < nums.size(); i++) {
      int x = nums[i];
      int sum = 0;
      while (x > 0) {
        sum += x % 10;
        x /= 10;
      }
      x = nums[i];
      if (v[sum] != -1)
        ans = max(ans, x + v[sum]);
      v[sum] = max(v[sum], x);
    }
    return ans;
  }
};

class Solution2 {
public:
  int maximumSum(vector<int> &nums) {
    int n = nums.size();
    vector<vector<int>> record(100);

    auto digit_sum = [&](int num) -> int {
      int sum = 0;
      while (num > 0) {
        sum += num % 10;
        num /= 10;
      }
      return sum;
    };

    for (int x: nums) {
      record[digit_sum(x)].emplace_back(x);
    }
    int ans = -1;
    for (auto &v: record) {
      if (v.size() > 1) {
        ranges::sort(v);
        ans = max(ans, v[v.size() - 1] + v[v.size() - 2]);
      }
    }
    return ans;
  }
};
