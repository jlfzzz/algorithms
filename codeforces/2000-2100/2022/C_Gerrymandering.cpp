#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> grid(2, vector<int>(n));
    {
        string s1, s2;
        cin >> s1;
        For(i, n) {
            if (s1[i] == 'A') {
                grid[0][i] = 1;
            }
        }
        cin >> s2;
        For(i, n) {
            if (s2[i] == 'A') {
                grid[1][i] = 1;
            }
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(3, -1));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            if (dp[i][j] != -1) {
                if (j == 0) {
                    if (i + 3 <= n) {
                        int contrib = 0;
                        {
                            int c1 = 0;
                            for (int k = 0; k < 3; k++) {
                                c1 += grid[0][i + k];
                            }
                            if (c1 >= 2) {
                                contrib++;
                            }
                        }
                        {
                            int c1 = 0;
                            for (int k = 0; k < 3; k++) {
                                c1 += grid[1][i + k];
                            }
                            if (c1 >= 2) {
                                contrib++;
                            }
                        }
                        dp[i + 3][0] = max(dp[i + 3][0], dp[i][j] + contrib);
                    }

                    if (i + 1 < n) {
                        int c1 = grid[1][i] + grid[0][i];
                        int t1 = c1 + grid[0][i + 1];
                        int t2 = c1 + grid[1][i + 1];

                        dp[i + 1][1] = max(dp[i + 1][1], dp[i][j] + (t1 >= 2));
                        dp[i + 1][2] = max(dp[i + 1][2], dp[i][j] + (t2 >= 2));
                    }
                } else if (j == 1) {
                    if (i + 4 <= n) {
                        int contrib = 0;
                        {
                            int c1 = 0;
                            for (int k = 0; k < 3; k++) {
                                c1 += grid[0][i + k + 1];
                            }
                            if (c1 >= 2) {
                                contrib++;
                            }
                        }
                        {
                            int c1 = 0;
                            for (int k = 0; k < 3; k++) {
                                c1 += grid[1][i + k];
                            }
                            if (c1 >= 2) {
                                contrib++;
                            }
                        }
                        dp[i + 3][1] = max(dp[i + 3][1], dp[i][j] + contrib);
                    }
                    if (i + 1 < n) {
                        int c1 = grid[1][i] + grid[0][i + 1] + grid[1][i + 1];
                        dp[i + 2][0] = max(dp[i + 2][0], dp[i][j] + (c1 >= 2));
                    }
                } else {
                    if (i + 4 <= n) {
                        int contrib = 0;
                        {
                            int c1 = 0;
                            for (int k = 0; k < 3; k++) {
                                c1 += grid[0][i + k];
                            }
                            if (c1 >= 2) {
                                contrib++;
                            }
                        }
                        {
                            int c1 = 0;
                            for (int k = 0; k < 3; k++) {
                                c1 += grid[1][i + k + 1];
                            }
                            if (c1 >= 2) {
                                contrib++;
                            }
                        }
                        dp[i + 3][2] = max(dp[i + 3][2], dp[i][j] + contrib);
                    }
                    if (i + 1 < n) {
                        int c1 = grid[0][i] + grid[0][i + 1] + grid[1][i + 1];
                        dp[i + 2][0] = max(dp[i + 2][0], dp[i][j] + (c1 >= 2));
                    }
                }
            }
        }
    }

    int ans = dp[n][0];
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
