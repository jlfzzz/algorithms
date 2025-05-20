//
// Created by 123 on 25-5-20.
//
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
  int maximumSum(vector<int> &nums) {
    int ans = -1;
    int mx[82]{}; // 至多 9 个 9 相加
    for (int num : nums) {
      int s = 0; // num 的数位和
      for (int x = num; x; x /= 10) { // 枚举 num 的每个数位
        s += x % 10;
      }
      if (mx[s]) { // 说明左边也有数位和等于 s 的元素
        ans = max(ans, mx[s] + num); // 更新答案的最大值
      }
      mx[s] = max(mx[s], num); // 维护数位和等于 s 的最大元素
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
