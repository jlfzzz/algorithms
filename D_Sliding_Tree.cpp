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
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    if (n == 1) {
        cout << -1 << '\n';
        return;
    }
    bool f = true;
    vector<int> deg(n + 1);
    for (int i = 1; i <= n; i += 1) {
        deg[i] = graph[i].size();
        if (deg[i] > 2)
            f = false;
    }
    if (f) {
        cout << -1 << '\n';
        return;
    }
    vector<vector<int>> id(n + 1);
    for (int i = 1; i <= n; i += 1)
        id[i].resize(graph[i].size());
    int tot = 0;
    for (int u = 1; u <= n; u += 1)
        for (int i = 0; i < graph[u].size(); i += 1)
            id[u][i] = tot++;
    vector<int> from(tot), to(tot);
    for (int u = 1; u <= n; u += 1)
        for (int i = 0; i < graph[u].size(); i += 1) {
            int v = graph[u][i];
            int eid = id[u][i];
            from[eid] = u;
            to[eid] = v;
        }
    vector<int> dist(tot, inf);
    queue<int> q;
    for (int u = 1; u <= n; u += 1)
        for (int i = 0; i < graph[u].size(); i += 1)
            if (deg[graph[u][i]] == 1) {
                int eid = id[u][i];
                dist[eid] = 0;
                q.push(eid);
            }
    while (!q.empty()) {
        int eid = q.front();
        q.pop();
        int u = from[eid], v = to[eid];
        for (int j = 0; j < graph[v].size(); j += 1) {
            int w = graph[v][j];
            if (w == u)
                continue;
            int nid = id[v][j];
            if (dist[nid] > dist[eid] + 1) {
                dist[nid] = dist[eid] + 1;
                q.push(nid);
            }
        }
    }
    int b = -1, c = -1;
    ll best = 4e18;
    for (int u = 1; u <= n; u += 1)
        if (deg[u] >= 3) {
            for (int i = 0; i < graph[u].size(); i += 1) {
                int v = graph[u][i];
                ll d = 1 + dist[id[u][i]];
                if (d < best) {
                    best = d;
                    b = u;
                    c = v;
                }
            }
        }
    int a = -1;
    for (int v: graph[b])
        if (v != c) {
            a = v;
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
