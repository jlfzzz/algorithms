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
    int x, y, k;
    cin >> x >> y >> k;

    int g = gcd(x, y);
    x /= g;
    y /= g;

    int n = max(x, y);
    vector<int> dp(n + 1, inf);

    auto dfs = [&](auto &dfs, int u) -> int {
        if (dp[u] != inf)
            return dp[u];
        if (u == 1)
            return dp[u] = 0;
        if (u <= k)
            return dp[u] = 1;
        for (int i = 2; i * i <= u && min(i, u / i) <= k; i++) {
            if (u % i != 0)
                continue;
            if (i <= k)
                dp[u] = min(dp[u], dfs(dfs, u / i) + 1);
            if (u / i <= k)
                dp[u] = min(dp[u], dfs(dfs, i) + 1);
        }
        return dp[u];
    };

    dfs(dfs, x);
    dfs(dfs, y);
    if (dp[x] == inf || dp[y] == inf)
        cout << -1 << '\n';
    else
        cout << dp[x] + dp[y] << '\n';
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
