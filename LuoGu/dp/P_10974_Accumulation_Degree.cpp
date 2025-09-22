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

    vector<vector<pii>> g(n + 1);
    For(i, n - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<map<int, int>> dp(n + 1);
    vector<int> sum(n + 1);
    auto dfs1 = [&](this auto &&dfs1, int u, int fa) -> int {
        int res = 0;

        for (auto &[v, w]: g[u]) {
            if (v == fa) {
                continue;
            }

            int t = 0;
            if (g[v].size() == 1) {
                t = w;
            } else {
                t = min(w, dfs1(v, u));
            }

            res += t;
            dp[u][v] = t;
        }

        sum[u] = res;
        return res;
    };

    dfs1(1, -1);

    int ans = 0;

    auto dfs2 = [&](this auto &&dfs2, int u, int fa) -> void {
        ans = max(ans, sum[u]);

        for (auto &[v, w]: g[u]) {
            if (v == fa) {
                continue;
            }

            int add;
            if (g[u].size() == 1) {
                add = w;
            } else {
                int t = sum[u] - dp[u][v];
                add = min(w, t);
            }
            int bak = sum[v];
            sum[v] = bak + add;
            dfs2(v, u);
            sum[v] = bak;
        }
    };

    dfs2(1, -1);

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
