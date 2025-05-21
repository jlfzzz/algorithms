#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007; //
// Created by 123 on 25-5-21.
//
class Solution {
public:
  int minZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    int n = nums.size();
    int m = queries.size();
    vector<int> diff(n + 1);
    int sum = 0;
    int k = 0;
    for (int i = 0; i < n; i++) {
      int x = nums[i];
      sum += diff[i];
      while (k < m && sum < x) {
        auto &q = queries[k];
        int l = q[0];
        int r = q[1];
        int val = q[2];
        diff[l] += val;
        diff[r + 1] -= val;
        if (i >= l && i <= r) {
          sum += val;
        }
        k++;
      }
      if (sum < x) {
        return -1;
      }
    }
    return k;
  }
};

class Solution2 {
public:
  int minZeroArray(vector<int> &nums, vector<vector<int>> &queries) {
    int n = nums.size();
    int m = queries.size();
    int lo = 0;
    int hi = m + 1;
    int ans = -1;

    while (lo < hi) {
      int mid = lo + (hi - lo) / 2;
      vector<int> diff(n + 1, 0);
      for (int i = 0; i < mid; i++) {
        auto &q = queries[i];
        diff[q[0]] += q[2];
        diff[q[1] + 1] -= q[2];
      }
      int sum = 0;
      int flag = true;
      for (int i = 0; i < n; i++) {
        sum += diff[i];
        if (nums[i] > sum) {
          flag = false;
          break;
        }
      }
      if (flag) {
        ans = mid;
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    return ans;
  }
};
