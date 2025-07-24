//
// Created by 123 on 25-5-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  int minimumCardPickup(vector<int>& cards) {
    unordered_map<int, int> dp;
    int n = cards.size();
    int ans = n + 1;
    for (int i = 0; i < n; i++) {
      int x = cards[i];
      if (dp.count(x)) {
        ans = min(ans, i - dp[x] + 1);
      }
      dp[x] = i;
    }
    return ans == n + 1 ? -1 : ans;
  }
};