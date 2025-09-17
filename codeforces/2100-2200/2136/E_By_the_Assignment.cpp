#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m, V;
    cin >> n >> m >> V;

    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    struct E {
        int to, id;
    };

    vector<vector<E>> g(n + 1);
    For(i, m) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, i + 1);
        g[v].emplace_back(u, i + 1);
    }

    auto q_pow = [&](int b, int e) -> int {
        int res = 1;
        while (e) {
            if (e & 1) {
                res = res * b % MOD;
            }
            b = b * b % MOD;
            e /= 2;
        }
        return res;
    };

    if (m == n - 1) {
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            if (a[i] == -1)
                cnt++;

        cout << q_pow(V, cnt) << '\n';
        return;
    }

    vector<int> dfn(n + 1), low(n + 1);
    vector<int> is_bridge(m + 1, 0);
    int ts = 0;

    auto dfs1 = [&](auto &&dfs1, int u, int pe) -> void {
        dfn[u] = low[u] = ++ts;
        for (auto e: g[u]) {
            int v = e.to, id = e.id;
            if (id == pe)
                continue;
            if (!dfn[v]) {
                dfs1(dfs1, v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u])
                    is_bridge[id] = 1;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };

    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            dfs1(dfs1, i, -1);

    vector<int> vis(n + 1, 0);
    vector<vector<int>> comps;
    auto dfs2 = [&](auto &&dfs2, int u, vector<int> &buf) -> void {
        vis[u] = 1;
        buf.push_back(u);
        for (auto e: g[u]) {
            if (is_bridge[e.id])
                continue;
            int v = e.to;
            if (!vis[v])
                dfs2(dfs2, v, buf);
        }
    };

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            vector<int> buf;
            dfs2(dfs2, i, buf);
            comps.push_back(std::move(buf));
        }
    }

    int ans = 1;
    vector<int> col(n + 1, -1);
    for (auto &comp: comps) {
        bool flag = true;
        vector<int> temp;
        temp.reserve(comp.size());
        auto dfs_color = [&](auto &&dfs_color, int u, int c) -> void {
            col[u] = c;
            temp.push_back(u);
            for (auto e: g[u]) {
                if (is_bridge[e.id])
                    continue;
                int v = e.to;
                if (col[v] == -1)
                    dfs_color(dfs_color, v, c ^ 1);
                else if (col[v] == c)
                    flag = false;
            }
        };

        if (!comp.empty())
            dfs_color(dfs_color, comp[0], 0);

        if (flag) {
            int t = -2;
            for (int u: comp) {
                if (a[u] != -1) {
                    if (t == -2)
                        t = a[u];
                    else if (t != a[u]) {
                        cout << 0 << '\n';
                        return;
                    }
                }
            }
            if (t == -2) {
                ans = ans * (V % MOD) % MOD;
            }
        } else {
            for (int u: comp) {
                if (a[u] != -1 && a[u] != 0) {
                    cout << 0 << '\n';
                    return;
                }
            }
        }

        for (int u: temp)
            col[u] = -1;
    }

    cout << ans % MOD << '\n';
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
