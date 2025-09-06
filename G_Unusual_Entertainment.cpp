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
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back((int) v);
        g[v].push_back((int) u);
    }
    vector<int> tin(n + 1), tout(n + 1), sz(n + 1);
    int ts = 0;
    auto dfs = [&](this auto &&dfs, int u, int p) -> void {
        tin[u] = ++ts;
        sz[u] = 1;
        for (int v: g[u])
            if (v != p) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        tout[u] = tin[u] + sz[u] - 1;
    };
    dfs(1, 0);

    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> p[i];

    struct Info {
        int x, id, sign;
    };
    vector<vector<Info>> ev(n + 1);
    for (int i = 0; i < q; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        ev[r].push_back({x, i, 1});
        if (l - 1 >= 0)
            ev[l - 1].push_back({x, i, -1});
    }

    vector<int> bit(n + 2, 0), ans(q, 0);
    auto add = [&](int idx, int val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    };
    auto query = [&](int idx) {
        int s = 0;
        for (; idx > 0; idx -= idx & -idx)
            s += bit[idx];
        return s;
    };

    for (int k = 0; k <= n; ++k) {
        if (k >= 1)
            add(tin[p[k]], 1);
        for (auto &e: ev[k]) {
            int cnt = query(tout[e.x]) - query(tin[e.x] - 1);
            ans[e.id] += e.sign * cnt;
        }
    }

    for (int i = 0; i < q; ++i)
        cout << (ans[i] > 0 ? "YES\n" : "NO\n");
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
