//
// Created by 123 on 25-5-26.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  int numWays(vector<string>& words, string target) {
    int n = words.size();
    int m = target.size();
    int l = words[0].size();
    vector<vector<ll>> memo(l, vector<ll>(26));
    for (int i = 0; i < l; i++) {
      for (int j = 0; j < n; j++) {
        char c = words[j][i];
        memo[i][c - 'a']++;
      }
    }

    vector<vector<ll>> dp(l + 1, vector<ll>(m + 1));
    dp[0][0] = 1LL;
    for (int i = 1; i <= l; i++) {
      dp[i][0] = 1LL;
      for (int j = 1; j <= min(m, i); j++) {
        ll curr = memo[i - 1][target[j - 1] - 'a'];
        // for (int k = 0; k < n; k++) {
        //   if (words[k][i - 1] == target[j - 1]) {
        //     curr++;
        //   }
        // }
        dp[i][j] = (curr * dp[i - 1][j - 1] % MOD + dp[i - 1][j]) % MOD;
      }
    }
    return dp[l][m];
  }
};