//
// Created by 123 on 25-5-20.
//
#include "bits/stdc++.h"
using namespace std;

class Solution {
public:
  int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++) {
      int num1 = nums1[i - 1];
      for (int j = 1; j <= n; j++) {
        int num2 = nums2[j - 1];
        if (num1 == num2) {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        } else {
          dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[m][n];
  }
};

class Solution2 {
public:
  int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    int ans = 0;
    unordered_map<int, vector<int>> mp;
    for (int i = 0; i < m; i++) {
      mp[nums2[i]].emplace_back(i);
    }

    vector<int> dp(n + 1, INT_MAX / 2);
    dp[0] = -1;
    for (int i = 0; i < n; i++) {
      auto& v = mp[nums1[i]];
      for (int j = i; j >= 0; j--) {
        int target = INT_MAX / 2;
        for (const int k : v) {
          if (k > dp[j] && k < target) {
            target = k;
          }
        }
        if (target != INT_MAX / 2) {
          dp[j + 1] = min(dp[j + 1], target);
          if (dp[j + 1] != INT_MAX / 2) {
            ans = max(ans, j + 1);
          }
        }
      }
    }
    return ans;
  }
};