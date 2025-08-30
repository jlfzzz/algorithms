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
    int a, b;
    cin >> a >> b;
    vector<vector<int>> g(n + 1, vector<int>());

    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dis(n + 1), pa(n + 1);
    auto dfs1 = [&](this auto &&dfs1, int u, int fa, int d) -> void {
        dis[u] = d;
        pa[u] = fa;
        for (int v: g[u]) {
            if (v != fa) {
                dfs1(v, u, d + 1);
            }
        }
    };

    dfs1(a, -1, 0);
    int d = dis[b];
    int ans = (d + 1) / 2;

    for (int i = 0; i < ans; i++) {
        b = pa[b];
    }

    dfs1(b, -1, 0);
    int max_d = 0;
    for (int i = 1; i <= n; i++) {
        max_d = max(max_d, dis[i]);
    }

    ans += 2 * (n - 1) - max_d;
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
