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
void solve2() {
    int n, m;
    cin >> n >> m;
    struct E {
        int to, id;
    };
    vector<vector<E>> g(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
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

    for (int i = 1; i <= n; ++i)
        if (!vis[i]) {
            vector<int> buf;
            dfs2(dfs2, i, buf);
            comps.push_back(std::move(buf));
        }

    cout << comps.size() << '\n';
    for (auto &c: comps) {
        cout << (int) c.size();
        for (auto x: c)
            cout << ' ' << x;
        cout << '\n';
    }
}


void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> g(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    vector<int> dfn(n + 1), low(n + 1);
    int ts = 0;
    stack<int> stk;
    vector<vector<int>> ans;

    auto dfs = [&](auto &&dfs, int u, int parent_edge) -> void {
        dfn[u] = low[u] = ++ts;
        stk.emplace(u);
        for (auto &[v, edge_id]: g[u]) {
            if (edge_id == parent_edge) {
                continue;
            }

            if (!dfn[v]) {
                dfs(dfs, v, edge_id);
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            vector<int> component;
            while (true) {
                int x = stk.top();
                stk.pop();
                component.push_back(x);
                if (x == u) {
                    break;
                }
            }
            ans.emplace_back(component);
        }
    };

    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            dfs(dfs, i, -1);
        }
    }

    cout << ans.size() << '\n';
    for (auto &c: ans) {
        cout << c.size() << ' ';
        for (auto x: c)
            cout << x << ' ';
        cout << '\n';
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
