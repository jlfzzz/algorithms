#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string lexicographicallySmallestString(string s) {
        int n = s.size();

        vector<vector<int>> valid(n, vector<int>(n, 0));
        vector<string> dp(n + 1);

        for (int len = 2; len <= n; len++) {
            for (int l = 0; l + len - 1 < n; l++) {
                int r = l + len - 1;
                int diff = abs(s[l] - s[r]);
                if (diff == 1 || diff == 25) {
                    if (len == 2 || valid[l + 1][r - 1]) {
                        valid[l][r] = 1;
                    }
                }

                if (!valid[l][r]) {
                    for (int k = l + 1; k < r; k += 2) {
                        if (valid[l][k] && valid[k + 1][r]) {
                            valid[l][r] = 1;
                            break;
                        }
                    }
                }
            }
        }

        dp[n] = "";
        for (int i = n - 1; i >= 0; i--) {
            dp[i] = s[i] + dp[i + 1];

            for (int j = i + 1; j < n; j++) {
                if (valid[i][j]) {
                    if (dp[j + 1] < dp[i]) {
                        dp[i] = dp[j + 1];
                    }
                }
            }
        }

        return dp[0];
    }
};
