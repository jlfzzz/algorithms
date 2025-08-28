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
    int n, t;
    cin >> n >> t;

    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dp0(n + 1, 0), dp1(n + 1, 0), ans(n + 1, 0);

    auto dfs1 = [&](this auto &&dfs1, int u, int fa) -> void {
        dp1[u] = 1; // true
        for (int v: g[u]) {
            if (v == fa)
                continue;
            dfs1(v, u);
            dp0[u] = dp0[u] | dp1[v];
            dp1[u] = dp1[u] & dp0[v];
        }
    };
    dfs1(1, 0);

    auto dfs2 = [&](this auto &&dfs2, int u, int fa) -> void {
        int cnt1 = 0, cnt2 = 0;
        dp0[u] = 0;
        dp1[u] = 1;
        for (int v: g[u]) {
            if (dp1[v]) {
                cnt1++;
                dp0[u] = 1;
            }
            if (!dp0[v]) {
                cnt2++;
                dp1[u] = 0;
            }
        }
        if (dp0[u])
            ans[u] = 1;
        else
            ans[u] = 0;

        for (int v: g[u]) {
            if (v == fa)
                continue;
            int tmp0 = dp0[u], tmp1 = dp1[u];
            if (cnt1 == 1 && dp1[v])
                dp0[u] = 0;
            if (cnt2 == 1 && !dp0[v])
                dp1[u] = 1;
            dfs2(v, u);
            dp0[u] = tmp0;
            dp1[u] = tmp1;
        }
    };
    dfs2(1, 0);

    For(i, t) {
        int start;
        cin >> start;
        cout << (ans[start] ? "Ron\n" : "Hermione\n");
    }
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
