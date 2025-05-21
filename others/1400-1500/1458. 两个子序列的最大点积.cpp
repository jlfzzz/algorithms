#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;

class Solution {
public:
  int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
    int n = nums1.size();
    int m = nums2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int x = nums1[i - 1];
        int y = nums2[j - 1];
        if (i == j) {
          dp[i][j] = max(dp[i - 1][j - 1] + x * y, x * y);
        } else {

        }
      }
    }
  }
};



class Solution2 {
public:
    int maxDotProduct(vector<int> &nums1, vector<int> &nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        vector<vector<int>> f(n1 + 1, vector<int>(n2 + 1, -1e8));
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                int tmp = nums1[i - 1] * nums2[j - 1];
                f[i][j] = max({ f[i][j - 1], f[i - 1][j], f[i - 1][j - 1] + tmp, tmp });
            }
        }
        return f[n1][n2];
    }
};