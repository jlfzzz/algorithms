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
    int getMoneyAmount(int n) {
        vector<vector<int>> memo(n + 1, vector<int>(n + 1, -1));

        auto dfs = [&](this auto &&dfs, int l, int r) -> int {
            if (l > r) {
                return 0;
            }

            if (l == r) {
                return 0;
            }

            int &x = memo[l][r];
            if (x != -1) {
                return x;
            }

            int res = INT_MAX;
            for (int j = l; j <= r; ++j) {
                int cost = j + max(dfs(l, j - 1), dfs(j + 1, r));
                res = min(res, cost);
            }

            return x = res;
        };

        return dfs(1, n);
    }
};
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for (int len = 2; len <= n; ++len) {
            for (int l = 1; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                dp[l][r] = INT_MAX;

                for (int j = l; j <= r; ++j) {
                    int cost = j + max(dp[l][j - 1], dp[j + 1][r]);
                    dp[l][r] = min(dp[l][r], cost);
                }
            }
        }

        return dp[1][n];
    }
};
