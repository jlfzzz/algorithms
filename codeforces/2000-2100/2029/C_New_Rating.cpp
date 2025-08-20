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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<vector<int>> dp(n, vector<int>(3));
    dp[0][0] = 1;
    dp[0][1] = 0;
    dp[0][2] = -inf;

    for (int i = 1; i < n; i++) {
        int x = a[i];
        if (x > dp[i - 1][0]) {
            dp[i][0] = dp[i - 1][0] + 1;
        } else if (x < dp[i - 1][0]) {
            dp[i][0] = dp[i - 1][0] - 1;
        } else {
            dp[i][0] = dp[i - 1][0];
        }

        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1]);

        if (x > dp[i - 1][2]) {
            dp[i][2] = dp[i - 1][2] + 1;
        } else if (x < dp[i - 1][2]) {
            dp[i][2] = dp[i - 1][2] - 1;
        } else {
            dp[i][2] = dp[i - 1][2];
        }

        if (x > dp[i - 1][1]) {
            dp[i][2] = max(dp[i][2], dp[i - 1][1] + 1);
        } else if (x < dp[i - 1][1]) {
            dp[i][2] = max(dp[i][2], dp[i - 1][1] - 1);
        } else {
            dp[i][2] = max(dp[i][2], dp[i - 1][1]);
        }
    }
    cout << max(dp[n - 1][1], dp[n - 1][2]) << '\n';
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
