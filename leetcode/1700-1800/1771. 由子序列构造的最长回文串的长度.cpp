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
    int longestPalindrome(string word1, string word2) {
        string t = word1 + word2;
        int n = t.size();

        // unordered_set<char> st;
        // for (char c: word1) {
        //     st.insert(c);
        // }

        // bool f = false;
        // for (char c: word2) {
        //     if (st.contains(c)) {
        //         f = true;
        //         break;
        //     }
        // }

        // if (!f) {
        //     return 0;
        // }

        int sz1 = word1.size(), sz2 = word2.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (t[i] == t[j]) {
                    if (i + 1 == j) {
                        dp[i][j] = 2;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    }
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < sz1; i++) {
            for (int j = sz1; j < n; j++) {
                if (t[i] == t[j]) {
                    ans = max(ans, 2 + (i + 1 <= j - 1 ? dp[i + 1][j - 1] : 0));
                }
            }
        }

        return ans;
    }
};
