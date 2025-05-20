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

    // 建立nums2中每个值的位置映射
    unordered_map<int, vector<int>> pos;
    for (int i = 0; i < m; i++) {
      pos[nums2[i]].push_back(i);
    }

    // dp[i]表示当形成i条线时，在nums2中的最小右边界
    // 初始化为-1，表示可以选择任意位置
    vector<int> dp(n + 1, -1);
    dp[0] = -1; // 0条线时，右边界为-1

    int result = 0;
    for (int i = 0; i < n; i++) {
      int x = nums1[i];
      // 从大到小遍历，避免重复计算
      for (int j = result; j >= 0; j--) {
        // 在nums2中找到大于dp[j]的x的最小位置
        int next_pos = INT_MAX;
        for (int pos_idx : pos[x]) {
          if (pos_idx > dp[j] && pos_idx < next_pos) {
            next_pos = pos_idx;
          }
        }

        if (next_pos != INT_MAX) {
          // 可以形成j+1条线，更新dp[j+1]
          dp[j + 1] = min(dp[j + 1] == -1 ? INT_MAX : dp[j + 1], next_pos);
          result = max(result, j + 1);
        }
      }
    }

    return result;
  }
};