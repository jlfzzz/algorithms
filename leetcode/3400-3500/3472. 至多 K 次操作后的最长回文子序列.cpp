#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;


class Solution {
public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1)));
        for (int i = 0; i < n; i++) {
            for (int c = 0; c <= k; c++) {
                dp[i][i][c] = 1;
            }
        }
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;

                auto f = [&](char a, char b) {
                    int d1 = abs(a - b);
                    int d2 = 26 - d1;
                    return min(d1, d2);
                };
                int d = f(s[i], s[j]);

                for (int c = 0; c <= k; c++) {
                    dp[i][j][c] = max(dp[i][j][c], dp[i + 1][j][c]);
                    dp[i][j][c] = max(dp[i][j][c], dp[i][j - 1][c]);

                    if (s[i] == s[j]) {
                        dp[i][j][c] = max(dp[i][j][c], dp[i + 1][j - 1][c] + 2);
                    } else if (c >= d) {
                        dp[i][j][c] = max(dp[i][j][c], dp[i + 1][j - 1][c - d] + 2);
                    }
                }
            }
        }

        return dp[0][n - 1][k];
    }
};
