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

    vector<vector<int>> g(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;

        g[p].push_back(i);
        g[i].push_back(p);
    }

    int ans = 0;
    vector<int> sz(n + 1);
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        sz[u] = 1;

        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            dfs(v, u);
            sz[u] += sz[v];
        }

        vector<int> dp(sz[u] + 1);
        dp[0] = 1;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            for (int j = sz[u]; j >= sz[v]; j--) {
                dp[j] |= dp[j - sz[v]];
            }
        }

        for (int i = sz[u] / 2; i >= 0; i--) {
            if (dp[i]) {
                ans += i * (sz[u] - 1 - i);
                return;
            }
        }
    };

    dfs(1, -1);

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
