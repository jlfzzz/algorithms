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

    vector<vector<pair<int, int>>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, 1});
        g[v].push_back({u, 1});
    }

    // 第一次DFS求直径端点
    vector<int> dis(n + 1), pa(n + 1);
    function<void(int, int, int)> dfs = [&](int u, int fa, int d) {
        dis[u] = d;
        pa[u] = fa;
        for (auto [v, w]: g[u]) {
            if (v != fa) {
                dfs(v, u, d + w);
            }
        }
    };

    dfs(1, 0, 0);
    int mx = 1;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > dis[mx])
            mx = i;
    }

    // 第二次DFS求直径
    dfs(mx, 0, 0);
    int end1 = mx, end2 = mx;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > dis[end2])
            end2 = i;
    }

    int L1 = dis[end2]; // 第一次直径长度

    if (k == 1) {
        cout << 2 * (n - 1) - L1 + 1 << '\n';
        return;
    }

    // 标记直径上的点
    vector<bool> on_diameter(n + 1, false);
    for (int u = end2; u != 0; u = pa[u]) {
        on_diameter[u] = true;
    }

    // 修改边权：直径上的边设为-1，其他保持1
    for (int u = 1; u <= n; u++) {
        for (auto &[v, w]: g[u]) {
            if (on_diameter[u] && on_diameter[v]) {
                w = -1;
            }
        }
    }

    // 树形DP求带权直径
    int L2 = 0;
    vector<int> d(n + 1, 0);
    function<void(int, int)> dp = [&](int u, int fa) {
        for (auto [v, w]: g[u]) {
            if (v == fa)
                continue;
            dp(v, u);
            L2 = max(L2, d[u] + d[v] + w);
            d[u] = max(d[u], d[v] + w);
        }
    };

    dp(1, 0);
    cout << 2 * n - L1 - L2 << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
