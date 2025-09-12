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
    int n, s;
    cin >> n >> s;

    vector<vector<pii>> g(n + 1, vector<pii>());
    For(i, n - 1) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    vector<int> pa(n + 1), dis(n + 1);
    auto dfs1 = [&](this auto &&dfs1, int u, int fa) -> void {
        pa[u] = fa;
        for (auto &[v, w]: g[u]) {
            if (v != fa) {
                dis[v] = dis[u] + w;
                dfs1(v, u);
            }
        }
    };

    dfs1(1, -1);
    int mx = 1;
    for (int i = 2; i <= n; i++) {
        if (dis[i] > dis[mx]) {
            mx = i;
        }
    }

    dis[mx] = 0;
    dfs1(mx, -1);
    for (int i = 1; i <= n; i++) {
        if (dis[i] > dis[mx]) {
            mx = i;
        }
    }

    int u = mx;
    dis[mx] = 0;
    dfs1(mx, -1);
    for (int i = 1; i <= n; i++) {
        if (dis[i] > dis[mx])
            mx = i;
    }
    int v = mx;

    vector<int> path;
    for (int x = v; x != -1; x = pa[x])
        path.push_back(x);
    reverse(path.begin(), path.end());

    vector<int> d;
    d.reserve(path.size());
    for (auto x: path)
        d.push_back(dis[x]);
    int m = (int) path.size();

    vector<char> on(n + 1, 0);
    for (auto x: path)
        on[x] = 1;

    int ans = inf;
    int j = 0;
    for (int i = 0; i < m; i++) {
        if (j < i)
            j = i;
        while (j + 1 < m && d[j + 1] - d[i] <= s)
            j++;
        ans = min(ans, max(d[i], d[m - 1] - d[j]));
    }

    vector<int> off(n + 1, 0);
    auto dfs2 = [&](this auto &&dfs2, int u, int fa) -> void {
        for (auto &[vv, ww]: g[u]) {
            if (vv == fa || on[vv])
                continue;
            off[vv] = off[u] + ww;
            dfs2(vv, u);
        }
    };
    for (int x: path) {
        off[x] = 0;
        dfs2(x, 0);
    }
    int branchMax = 0;
    for (int i = 1; i <= n; i++)
        branchMax = max(branchMax, off[i]);
    ans = max(ans, branchMax);

    cout << ans << '\n';
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
