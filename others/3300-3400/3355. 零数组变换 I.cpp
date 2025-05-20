//
// Created by 123 on 25-5-20.
//
#include "bits/stdc++.h"
using namespace std;


class Solution {
public:
  bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    int n = nums.size();
    int m = queries.size();
    for (int i = 0; i < n; i++) {
      int x = nums[i];
      vector<int> dp(x + 1, false);
      dp[0] = true;
      for (int j = 0; j < m; j++) {
        int l = queries[j][0];
        int r = queries[j][1];
        if (i >= l && i <= r) {
          for (int k = 1; k <= x; k++) {

          }
        }
      }
    }
  }
};