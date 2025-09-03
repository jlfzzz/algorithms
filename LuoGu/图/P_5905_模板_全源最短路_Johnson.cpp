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

// 重边和负环
// vector<unordered_map<int, int>> g(n + 1);
// for (int i = 0; i < m; i++) {
//     int u, v, w;
//     cin >> u >> v >> w;
//     if (u == v) {
//         if (w < 0) {
//             cout << -1 << '\n';
//             return;
//         }
//     } else {
//         if (g[u].count(v)) {
//             g[u][v] = min(g[u][v], w);
//         } else {
//             g[u][v] = w;
//         }
//     }
// }

// vector<vector<pii>> adj(n + 1);
// for (int u = 1; u <= n; u++) {
//     for (auto [v, w]: g[u]) {
//         adj[u].emplace_back(v, w);
//     }
// }

// for (int i = 1; i <= n; i++) {
//     adj[0].emplace_back(i, 0);
// }

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<pii>> adj(n + 1, vector<pii>());
    For(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
    }

    for (int i = 1; i <= n; i++) {
        adj[0].emplace_back(i, 0);
    }

    vector<int> dis(n + 1, inf), cnt(n + 1);
    vector<bool> vis(n + 1);
    dis[0] = 0;

    auto spfa = [&]() {
        queue<int> q;
        q.push(0);
        vis[0] = true;

        while (!q.empty()) {
            int x = q.front();
            q.pop();
            vis[x] = false;

            for (auto &[v, w]: adj[x]) {
                if (dis[x] + w < dis[v]) {
                    dis[v] = dis[x] + w;


                    if (!vis[v]) {
                        cnt[v] = cnt[x] + 1;
                        if (cnt[v] >= n) {
                            return false;
                        }
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return true;
    };

    if (!spfa()) {
        cout << -1 << '\n';
        return;
    }

    vector<int> h = dis;
    vector<vector<pii>> new_g(n + 1);
    for (int u = 1; u <= n; u++) {
        for (auto [v, w]: adj[u]) {
            if (u != 0) {
                int new_w = w + h[u] - h[v];
                new_g[u].emplace_back(v, new_w);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        vector<int> dist(n + 1, inf);
        dist[i] = 0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.emplace(0, i);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u])
                continue;
            for (auto [v, w]: new_g[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }
        }

        int ans = 0;
        for (int j = 1; j <= n; j++) {
            if (dist[j] == inf) {
                ans += j * int(1e9);
            } else {
                int actual = dist[j] - h[i] + h[j];
                ans += j * actual;
            }
        }
        cout << ans << '\n';
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
