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

constexpr int N = 64;
constexpr int M = 17;
int dp[N][N];
// bool choose[M];
int cost[M + 1];

void init() {
    cost[0] = 1;
    for (int i = 1; i <= M; i++)
        cost[i] = cost[i - 1] * 2;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            dp[i][j] = LONG_LONG_MAX;
    dp[0][0] = 0;
    for (int k = 1; k <= M; k++) {
        for (int a = N - 1; a >= 0; a--) {
            for (int b = N - 1; b >= 0; b--) {
                if (dp[a][b] == LONG_LONG_MAX)
                    continue;
                if (a + k < N)
                    dp[a + k][b] = min(dp[a + k][b], dp[a][b] + cost[k]);
                if (b + k < N)
                    dp[a][b + k] = min(dp[a][b + k], dp[a][b] + cost[k]);
            }
        }
    }
}

void solve() {
    int x, y;
    cin >> x >> y;

    int b1 = bit_width((ull) x), b2 = bit_width((ull) y);
    int len1 = b1 - 1, len2 = b2 - 1;
    int len = 0;
    while (len1 >= 0 && len2 >= 0) {
        if ((x >> len1 & 1) == (y >> len2 & 1)) {
            len1--, len2--;
            len++;
        } else {
            break;
        }
    }

    int need1 = b1 - len, need2 = b2 - len;
    // int ans = LONG_LONG_MAX;
    // while (true) {
    //     need1 = min(need1, b1), need2 = min(need2, b2);

    //     auto f = [&]() { int res = LONG_LONG_MAX; };
    // }
    // cout << dp[need1][need2] << '\n';
    int ans = LONG_LONG_MAX;
    for (int d = 0; need1 + d < N && need2 + d < N; d++) {
        ans = min(ans, dp[need1 + d][need2 + d]);
    }
    // for (int a = need1 + len; a < N; a++) {
    //     for (int b = need2 + len; b < N; b++) {
    //         ans = min(ans, dp[a][b]);
    //     }
    // }
    for (int a = b1; a < N; a++) {
        for (int b = b2; b < N; b++) {
            ans = min(ans, dp[a][b]);
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
