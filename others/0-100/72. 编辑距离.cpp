#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;


class Solution {
public:
  int minDistance(string word1, string word2) {
    int n = word1.size();
    int m = word2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));
    dp[0][0] = 0;
    for (int i = 1; i <= m; i++) {
      dp[0][i] = i;
    }
    for (int i = 1; i <= n; i++) {
      dp[i][0] = i;
      for (int j = 1; j <= m; j++) {
        if (word1[i - 1] == word2[j - 1]) {
          dp[i][j] = dp[i - 1][j - 1];
        } else {
          dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
        }
      }
    }
    return dp[n][m];
  }
};


class Solution2 {
public:
  int minDistance(string word1, string word2) {
    int n = word1.length(), m = word2.length();
    vector f(n + 1, vector<int>(m + 1));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
      f[i][0] = i;
    }

    for (int i = 1; i <= m; i++) {
      f[0][i] = i;
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        f[i + 1][j + 1] = word1[i] == word2[j] ? f[i][j] : min(min(f[i][j + 1], f[i + 1][j]), f[i][j]) + 1;
      }
    }
    return f[n][m];
  }
};
