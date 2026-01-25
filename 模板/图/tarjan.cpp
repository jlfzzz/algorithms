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

// 有向图求scc。缩点
void solve1() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    int cnt = 0;
    int timestamp = 0;
    vector<int> dfn(n + 1), low(n + 1), in_stack(n + 1), comp(n + 1);
    vector<vector<int>> comps;
    stack<int> stk;

    auto tarjan = [&](this auto &&tarjan, int u) -> void {
        dfn[u] = low[u] = ++timestamp;
        stk.push(u);
        in_stack[u] = true;

        for (int v: g[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            vector<int> scc;
            while (true) {
                int x = stk.top();
                stk.pop();
                in_stack[x] = false;
                comp[x] = comps.size() + 1;
                scc.push_back(x);
                if (x == u)
                    break;
            }
            comps.emplace_back(scc);
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    cout << cnt << '\n';
}

// 割边，桥
void solve2() {
    int n, m;
    cin >> n >> m;
    struct E {
        int to, id;
    };
    vector<vector<E>> g(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    vector<int> dfn(n + 1), low(n + 1);
    int ts = 0;
    vector<pii> bridges;
    vector<int> sz(n + 1), blockId(n + 1);
    int bid = 0;
    map<int, int> blockSz;
    auto tarjan = [&](this auto &&tarjan, int u, int pe) -> void {
        dfn[u] = low[u] = ++ts;
        blockId[u] = bid;
        sz[u] = 1;
        for (auto e: g[u]) {
            if (e.id == pe)
                continue;
            int v = e.to;
            if (!dfn[v]) {
                tarjan(v, e.id);
                low[u] = min(low[u], low[v]);
                sz[u] += sz[v];
                if (low[v] > dfn[u]) {
                    bridges.emplace_back(u, v);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, -1);
            blockSz[bid] = sz[i];
            bid++;
        }
    }

    ranges::sort(bridges);
    for (auto &[x, y]: bridges) {
        cout << x << ' ' << y << '\n';
    }
}

// 割点
void solve3() {
    int n, m;
    cin >> n >> m;
    struct E {
        int to, id;
    };
    vector<vector<E>> g(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    vector<int> dfn(n + 1), low(n + 1), cut(n + 1);
    int timestamp = 0;

    auto tarjan = [&](this auto &&tarjan, int u, int pe) -> void {
        dfn[u] = low[u] = ++timestamp;
        int child = 0;
        for (auto e: g[u]) {
            if (e.id == pe)
                continue;
            int v = e.to;
            if (!dfn[v]) {
                tarjan(v, e.id);
                low[u] = min(low[u], low[v]);
                if (pe != -1 && low[v] >= dfn[u])
                    cut[u] = 1;
                child++;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (pe == -1 && child > 1)
            cut[u] = 1;
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, -1);
        }
    }

    vector<int> res;
    for (int i = 1; i <= n; i++)
        if (cut[i])
            res.push_back(i);
    cout << res.size() << '\n';
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << (i + 1 == res.size() ? '\n' : ' ');
}

// 边双,edcc。先找桥，再dfs一遍收集
void solve4() {
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

    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            vector<int> buf;
            dfs2(dfs2, i, buf);
            comps.push_back(std::move(buf));
        }
    }

    cout << comps.size() << '\n';
    for (auto &c: comps) {
        cout << (int) c.size();
        for (auto x: c)
            cout << ' ' << x;
        cout << '\n';
    }
}

// 点双 vdcc
void solve5() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dfn(n + 1), low(n + 1);
    int ts = 0;
    vector<int> st;
    vector<vector<int>> comps;

    auto dfs = [&](auto &&dfs, int u, int fa) -> void {
        dfn[u] = low[u] = ++ts;
        st.push_back(u);
        int son = 0;
        for (int v: g[u]) {
            if (!dfn[v]) {
                son++;
                dfs(dfs, v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    vector<int> comp;
                    while (!st.empty() && st.back() != v) {
                        comp.push_back(st.back());
                        st.pop_back();
                    }
                    if (!st.empty()) {
                        comp.push_back(v);
                        st.pop_back();
                    }
                    comp.push_back(u);
                    comps.push_back(std::move(comp));
                }
            } else if (v != fa) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (fa == 0 && son == 0) {
            vector<int> c;
            c.push_back(u);
            comps.push_back(std::move(c));
        }
    };

    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            st.clear();
            dfs(dfs, i, 0);
        }
    }

    cout << comps.size() << '\n';
    for (auto &c: comps) {
        cout << (int) c.size();
        for (auto x: c)
            cout << ' ' << x;
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
        solve1();
    return 0;
}
