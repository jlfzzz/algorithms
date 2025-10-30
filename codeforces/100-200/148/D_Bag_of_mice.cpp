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
    int w, b;
    cin >> w >> b;

    vector<vector<double>> dp(w + 1, vector<double>(b + 1));

    for (int i = 1; i <= w; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= b; j++) {
            dp[i][j] += (double) i / (i + j);

            if (j >= 2) {
                dp[i][j] += (double) j / (i + j) * (j - 1) / (i + j - 1) * i / (i + j - 2) * dp[i - 1][j - 2];
            }

            if (j >= 3) {
                dp[i][j] += (double) j / (i + j) * (j - 1) / (i + j - 1) * (j - 2) / (i + j - 2) * dp[i][j - 3];
            }
        }
    }

    double ans = dp[w][b];
    printf("%.9lf\n", ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
