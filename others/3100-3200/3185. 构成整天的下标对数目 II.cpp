//
// Created by 123 on 25-5-24.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  long long countCompleteDayPairs(vector<int>& hours) {
    unordered_map<int, int> dp;
    long long ans = 0;
    for (int h : hours) {
      ans += dp[(24 - (h % 24)) % 24];
      dp[h % 24]++;
    }
    return ans;
  }
};