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
        solve();
    return 0;
}
