#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    int n = s1.size();
    int m = s2.size();
    if (n + m != s3.size()) {
      return false;
    }

    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
    dp[0][0] = true;
    for (int i = 1; i <= n; i++) {
      dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
    }
    for (int j = 1; j <= m; j++) {
      dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (s1[i - 1] == s3[i + j - 1]) {
          dp[i][j] = dp[i][j] || dp[i - 1][j];
        }
        if (s2[j - 1] == s3[i + j - 1]) {
          dp[i][j] = dp[i][j] || dp[i][j - 1];
        }
      }
    }
    return dp[n][m];
  }
};


class Solution {
public:
  bool isInterleave(string s1, string s2, string s3) {
    int n = s1.size(), m = s2.size();
    if (n + m != s3.size()) {
      return false;
    }

    vector f(n + 1, vector<int>(m + 1));
    f[0][0] = true;
    for (int j = 0; j < m; j++) {
      f[0][j + 1] = s2[j] == s3[j] && f[0][j];
    }
    for (int i = 0; i < n; i++) {
      f[i + 1][0] = s1[i] == s3[i] && f[i][0];
      for (int j = 0; j < m; j++) {
        f[i + 1][j + 1] = s1[i] == s3[i + j + 1] && f[i][j + 1] || s2[j] == s3[i + j + 1] && f[i + 1][j];
      }
    }
    return f[n][m];
  }
};
