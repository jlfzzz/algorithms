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
    vector<vector<int>> graph(n + 1, vector<int>());
    vector<int> deg(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        deg[v]++, deg[u]++;
    }
    if (n == 1) {
        cout << -1 << '\n';
        return;
    }
    vector<int> dist(n + 1), p(n + 1);
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        p[u] = fa;
        for (int v: graph[u])
            if (v != fa) {
                dist[v] = dist[u] + 1;
                dfs(v, u);
            }
    };
    dist[1] = 0;
    dfs(1, -1);
    int x = 1;
    for (int i = 1; i <= n; i += 1)
        if (dist[i] > dist[x])
            x = i;
    dist[x] = 0;
    dfs(x, -1);
    int y = x;
    for (int i = 1; i <= n; i += 1)
        if (dist[i] > dist[y])
            y = i;
    if (dist[y] == n - 1) {
        cout << -1 << '\n';
        return;
    }
    vector<int> on(n + 1);
    int cur = y;
    while (cur != -1) {
        on[cur] = 1;
        cur = p[cur];
    }
    int a = -1, b = -1, c = -1;
    for (int u = 1; u <= n; u += 1)
        if (on[u]) {
            for (int v: graph[u])
                if (!on[v]) {
                    if (p[u] != -1) {
                        a = p[u];
                        b = u;
                        c = v;
                    } else {
                        for (int w: graph[u])
                            if (on[w]) {
                                a = w;
                                b = u;
                                c = v;
                                break;
                            }
                    }
                    if (a != -1)
                        break;
                }
            if (a != -1)
                break;
        }
    cout << a << ' ' << b << ' ' << c << '\n';
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
