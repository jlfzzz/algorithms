//
// Created by 123 on 25-5-22.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

// q233

class Solution {
public:
  int countDigitOne(int n) {
    int len = to_string(n).length();
    string s = to_string(n);
    vector dp(len, vector<ll>(len, -1));

    auto dfs = [&](this auto &&dfs, int idx, int is_limit, int is_num, ll count) -> ll {
      if (idx == len) {
        if (is_num) {
          return count;
        }
        return 0;
      }

      if (!is_limit && is_num && dp[idx][count] != -1) {
        return dp[idx][count];
      }

      ll sum = 0;
      int hi = is_limit ? s[idx] - '0' : 9;
      int lo = 0;

      for (int i = lo; i <= hi; i++) {
        sum += dfs(idx + 1, is_limit && i == hi, !(!is_num && i == 0), count + (i == 1));
      }

      if (!is_limit && is_num) {
        dp[idx][count] = sum;
      }
      return sum;
      };
    return dfs(0, 1, 0, 0);
  }
};