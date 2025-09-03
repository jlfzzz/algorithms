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
    vector<vector<int>> g(n + 1, vector<int>(n + 1, inf));
    vector<vector<int>> dis(n + 1, vector<int>(n + 1, inf));

    for (int i = 1; i <= n; i++) {
        g[i][i] = 0;
        dis[i][i] = 0;
    }

    For(i, m) {
        int u, v, d;
        cin >> u >> v >> d;
        g[u][v] = min(g[u][v], d);
        g[v][u] = min(g[v][u], d);
        dis[u][v] = min(dis[u][v], d);
        dis[v][u] = min(dis[v][u], d);
    }

    ll ans = inf;
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                if (dis[i][j] != inf && g[i][k] != inf && g[k][j] != inf) {
                    ans = min(ans, dis[i][j] + g[i][k] + g[k][j]);
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (dis[i][k] == inf)
                continue;
            for (int j = 1; j <= n; j++) {
                if (dis[k][j] != inf) {
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                }
            }
        }
    }

    if (ans == inf) {
        cout << "No solution." << endl;
    } else {
        cout << ans << endl;
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
