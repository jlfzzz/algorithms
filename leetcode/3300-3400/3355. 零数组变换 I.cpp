//
// Created by 123 on 25-5-20.
//
#include "bits/stdc++.h"
using namespace std;


class Solution {
public:
  bool isZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    int n = nums.size();
    vector<int> diff(n + 1);
    for (auto &q: queries) {
      // 区间 [l,r] 中的数都加一
      diff[q[0]]++;
      diff[q[1] + 1]--;
    }

    int sum_d = 0;
    for (int i = 0; i < n; i++) {
      sum_d += diff[i];
      // 此时 sum_d 表示 nums[i] 要减掉多少
      if (nums[i] > sum_d) { // nums[i] 无法变成 0
        return false;
      }
    }
    return true;
  }
};
