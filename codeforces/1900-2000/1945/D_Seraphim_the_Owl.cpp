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
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    vector<int> pre(n + 1);
    For(i, n) pre[i + 1] = pre[i] + b[i];

    int mn = n;
    vector<int> dp(n + 1, inf);
    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        dp[i] = dp[mn] + a[i] + pre[mn] - pre[i + 1];
        if (dp[i] + pre[i] < dp[mn] + pre[mn]) {
            mn = i;
        }
    }

    int ans = inf;
    for (int i = 0; i < m; i++) {
        ans = min(ans, dp[i]);
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
