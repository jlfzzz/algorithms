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
  int maxDistance(vector<vector<int>>& arrays) {
    int ans = 0;
    int mn = INT_MAX / 2, mx = INT_MIN / 2; // 防止减法溢出
    for (auto& a : arrays) {
      ans = max({ans, a.back() - mn, mx - a[0]});
      mn = min(mn, a[0]);
      mx = max(mx, a.back());
    }
    return ans;
  }
};