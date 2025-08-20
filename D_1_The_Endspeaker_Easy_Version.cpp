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
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];
    vector<int> b(m + 1);
    For(i, m) cin >> b[i + 1];

    if (ranges::max(a) > ranges::max(b)) {
        cout << -1 << '\n';
        return;
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, inf));
    for (int i = 0; i <= m; i++) {
        dp[0][i] = 0;
    }
    vector<int> pre_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        pre_sum[i] = pre_sum[i - 1] + a[i];
    }
    pre_sum.push_back(inf);

    for (int i = 1; i <= n; i++) {
        int pre_min = inf;
        for (int j = 1; j <= m; j++) {
            int k = ranges::upper_bound(pre_sum, pre_sum[i - 1] + b[j]) - pre_sum.begin() - 1;
            if (k < i)
                break;

            pre_min = min(pre_min, dp[i - 1][j]);
            dp[k][j] = min(dp[k][j], pre_min + m - j);
        }
    }

    int ans = ranges::min(dp[n]);
    cout << (ans == inf ? -1 : ans) << '\n';
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
