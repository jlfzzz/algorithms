#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m, d;
    cin >> n >> m >> d;
    vector<vector<char>> grid(n + 1, vector<char>(m + 1));
    For(i, n) {
        For(j, m) { cin >> grid[i + 1][j + 1]; }
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    {
        int r = 1, l = 1;
        int window = 0;
        for (int i = 1; i <= m; i++) {
            while (l <= i && i - l > d) {
                if (grid[n][l] == 'X') {
                    window--;
                }
                l++;
            }
            while (r <= m && r - i <= d) {
                if (grid[n][r] == 'X') {
                    window++;
                }
                r++;
            }

            if (grid[n][i] == '#') {
                continue;
            }
            dp[n][i] = window;
        }
    }

    // for (int i = 1; i <= m; i++) {
    //     cout << "col is: " << i << ' ' << "dp[n][col] is :" << dp[n][i] << endl;
    // }

    for (int i = n - 1; i >= 1; i--) {
        int r = 1;
        int l = 1;
        int window = 0;
        for (int j = 1; j <= m; j++) {
            while (l <= j && 1 + (j - l) * (j - l) > d * d) {
                window = (window - dp[i + 1][l] + MOD) % MOD;
                l++;
            }
            while (r <= m && 1 + (r - j) * (r - j) <= d * d) {
                window += dp[i + 1][r];
                if (window > MOD) {
                    window -= MOD;
                }
                r++;
            }
            if (grid[i][j] == '#') {
                continue;
            }
            dp[i][j] = window;
        }

        l = 1, r = 1;
        window = 0;
        auto temp = dp[i];
        for (int j = 1; j <= m; j++) {
            while (l <= j && j - l > d) {
                window = (window - temp[l] + MOD) % MOD;
                l++;
            }
            while (r <= m && r - j <= d) {
                window = (window + temp[r]) % MOD;
                r++;
            }
            if (grid[i][j] == '#') {
                continue;
            }

            dp[i][j] = (dp[i][j] + window - temp[j] + MOD) % MOD;
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        if (grid[1][i] == 'X') {
            ans = (ans + dp[1][i]) % MOD;
        }
    }

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
