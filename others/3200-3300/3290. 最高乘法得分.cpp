//
// Created by 123 on 25-5-23.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  long long maxScore(vector<int>& a, vector<int>& b) {
    int n = b.size();
    vector<vector<long long>> dp(5, vector<long long>(n + 1));
    for (int i = 1; i <= 4; i++) {
      dp[i][0] = LONG_LONG_MIN / 2;
      for (int j = 1; j <= n; j++) {
        dp[i][j] = max(dp[i][j - 1], dp[i - 1][j - 1] + 1ll * a[i - 1] * b[j - 1]);
      }
    }
    return dp[4][n];
  }
};

class Solution2 {
public:
  long long maxScore(vector<int>& a, vector<int>& b) {
    int n = b.size();
    vector<array<long long, 5>> f(n + 1);
    for (int j = 1; j < 5; j++) {
      f[0][j] = LLONG_MIN / 2;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 4; j++) {
        f[i + 1][j + 1] = max(f[i][j + 1], f[i][j] + (long long) a[j] * b[i]);
      }
    }
    return f[n][4];
  }
};