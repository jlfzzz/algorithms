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
    int n, m, h;
    cin >> n >> m >> h;
    vector<int> horses(h);
    for (int i = 0; i < h; i++) {
        cin >> horses[i];
        horses[i]--;
    }
    vector<vector<pair<int, int>>> g(2 * n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        g[u + n].push_back({v + n, w / 2});
        g[v + n].push_back({u + n, w / 2});
    }
    for (int a: horses) {
        g[a].push_back({a + n, 0});
    }

    auto dij = [&](int start, vector<int> &dist) {
        dist.assign(2 * n, inf);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[start] = 0;
        pq.push({0, start});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u])
                continue;
            for (auto [v, w]: g[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
    };

    vector<int> distM, distR;
    dij(0, distM);
    dij(n - 1, distR);

    int ans = inf;
    for (int i = 0; i < n; i++) {
        ans = min(ans, max(distM[i], distR[i]));
        ans = min(ans, max(distM[i], distR[i + n]));
        ans = min(ans, max(distM[i + n], distR[i]));
        ans = min(ans, max(distM[i + n], distR[i + n]));
    }

    if (ans == inf) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
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
