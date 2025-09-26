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
    vector<map<int, int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u][v] = i + 1;
        g[v][u] = i + 1;
    }
    if (n % 3 != 0) {
        cout << -1 << '\n';
        return;
    }

    vector<int> parent(n + 1), deg(n + 1);

    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        parent[u] = fa;

        for (auto [v, id]: g[u]) {
            if (v == fa) {
                continue;
            }

            dfs(v, u);
        }
    };

    dfs(1, 0);

    vector<vector<pii>> g2(n + 1);
    for (int i = 2; i <= n; ++i) {
        int p = parent[i];
        g2[i].emplace_back(p, g[i][p]);
        deg[p]++;
    }

    deque<int> dq;
    for (int i = 1; i <= n; ++i)
        if (deg[i] == 0)
            dq.push_back(i);

    vector<int> sz(n + 1, 1), deleted(n + 1, 0);
    vector<int> ans;

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        if (deleted[u])
            continue;
        deleted[u] = 1;

        int p = parent[u];
        if (sz[u] == 3) {
            if (p != 0) {
                ans.push_back(g2[u][0].second);
                deg[p]--;
                if (deg[p] == 0)
                    dq.push_back(p);
            }
        } else {
            if (p == 0) {
                continue;
            }
            if (deleted[p]) {
                cout << -1 << '\n';
                return;
            }
            sz[p] += sz[u];
            deg[p]--;
            if (deg[p] == 0)
                dq.push_back(p);
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (!deleted[i]) {
            cout << -1 << '\n';
            return;
        }
    }

    int expected = n / 3 - 1;
    if ((int) ans.size() != expected) {
        cout << -1 << '\n';
        return;
    }

    cout << ans.size() << '\n';
    for (int id: ans)
        cout << id << ' ';
    cout << '\n';
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
