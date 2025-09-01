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
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    vector<vector<int>> dp(n + 2, vector<int>(k + 1, inf));
    dp[1][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int c = 0; c <= k; ++c) {
            if (dp[i][c] == inf) {
                continue;
            }
            int mn = inf;
            for (int j = 0; i + j <= n && j + c <= k; j++) {
                mn = min(mn, a[i + j]);
                dp[i + j + 1][j + c] = min(dp[i + j + 1][j + c], dp[i][c] + mn * (j + 1));
            }
        }
    }

    ll ans = ranges::min(dp[n + 1]);
    cout << ans << "\n";
}
void solve2() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    a[0] = inf;

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, inf));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        int x = a[i];
        for (int c = 0; c <= k; c++) {
            int mn = inf;
            for (int j = i - 1; j >= 0 && i - j - 1 <= c; j--) {
                mn = min(mn, a[j + 1]);
                dp[i][c] = min(dp[i][c], dp[j][c - (i - j - 1)] + mn * (i - j));
            }
        }
    }

    int ans = ranges::min(dp[n]);
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
