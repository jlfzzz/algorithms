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
    int n, k;
    cin >> n >> k;

    vector<vector<int>> g(n + 1, vector<int>());
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dis(n + 1);
    vector<int> pa(n + 1);
    auto dfs = [&](this auto &&dfs, int u, int fa, int d) -> void {
        dis[u] = d;
        pa[u] = fa;
        for (int v: g[u]) {
            if (v != fa) {
                dfs(v, u, d + 1);
            }
        }
    };
    dfs(1, -1, 0);

    int mx = 0;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > dis[mx])
            mx = i;
    }

    for (int i = 0; i <= n; i++) {
        pa[i] = 0;
        dis[i] = 0;
    }

    dfs(mx, -1, 0);
    int mx1 = 0, mx2 = 0;

    for (int i = 1; i <= n; i++) {
        if (dis[i] > dis[mx1]) {
            mx2 = mx1, mx1 = i;
        } else if (dis[i] > dis[mx2]) {
            mx2 = i;
        }
    }

    vector<int> on_d1(n + 1), on_d2(n + 1);
    {
        int t = mx1;
        while (pa[t] != -1) {
            on_d1[t] = 1;
            t = pa[t];
        }
        on_d1[t] = 1;
    }
    {
        int t = mx2;
        while (pa[t] != -1) {
            on_d2[t] = 1;
            t = pa[t];
        }
        on_d2[t] = 1;
    }

    int total = 2 * (n - 1);
    
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
