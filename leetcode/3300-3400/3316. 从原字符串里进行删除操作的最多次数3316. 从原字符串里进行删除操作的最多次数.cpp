//
// Created by 123 on 25-5-25.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
    int n = source.length();
    int m = pattern.length();
    vector memo(n, vector<int>(max(m, n) + 1, -1));
    unordered_set<int> st(targetIndices.begin(), targetIndices.end());

    auto dfs = [&](this auto&&dfs, int i, int j) -> int {
      if (i == n) {
        return j == m ? 0 : INT_MIN;
      }

      if (m - j > n - i) return INT_MIN;

      if (memo[i][j] != -1) {
        return memo[i][j];
      }

      int& res = memo[i][j];
      if (source[i] == pattern[j]) {
        res = max(st.contains(i) + dfs(i + 1, j), dfs(i + 1, j + 1));
      } else {
        res = st.contains(i) + dfs(i + 1, j);
      }
      return res;
    };
    return dfs(0, 0);
  }
};

class Solution2 {
public:
  int maxRemovals(string source, string pattern, vector<int> &targetIndices) {
    int n = source.length();
    int m = pattern.length();
    set st(targetIndices.begin(), targetIndices.end());

    vector dp(n + 1, vector<int>(m + 1, -1));
    auto dfs = [&](this auto &&dfs, int i, int j) -> int {
      if (i == n) {
        return j == m ? 0 : INT_MIN;
      }

      int &res = dp[i][j];
      if (res != -1) {
        return res;
      }

      if (source[i] != pattern[j]) {
        if (st.contains(i)) {
          res = 1 + dfs(i + 1, j);
        } else {
          res = dfs(i + 1, j);
        }
      } else {
        if (st.contains(i)) {
          res = max(1 + dfs(i + 1, j), dfs(i + 1, j + 1));
        } else {
          res = dfs(i + 1, j + 1);
        }
      }
      return res;
    };
    return dfs(0, 0);
  }
};
