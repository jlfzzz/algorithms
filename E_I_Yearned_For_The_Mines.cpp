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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}






void solve() {
    int n;
    cin >> n;

    vector<vector<int>> graph(n + 1, vector<int>());
    vector<int> parent(n + 1);
    vector<bool> in(n + 1, false), vis(n + 1, false);
    vector<int> v;

    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto add = [&](int u) -> void {
        if (in[u])
            return;
        in[u] = true;
        vis[u] = true;
        v.push_back(u);
        for (int v: graph[u]) {
            vis[v] = true;
        }
    };

    auto dfs = [&](this auto &&dfs, int u, int p) -> void {
        parent[u] = p;
        int cnt = 0;
        for (int v: graph[u]) {
            if (v == p)
                continue;
            dfs(v, u);
            if (!vis[v])
                cnt++;
        }
        if (cnt >= 3)
            add(u);
    };

    dfs(1, 0);

    for (int i = 2; i <= n; i++) {
        if (!vis[i])
            add(parent[i]);
    }

    int k = n + v.size();
    cout << k << "\n";
    for (int x: v)
        cout << "1 " << x << "\n";
    for (int x: v)
        cout << "2 " << x << "\n";
    for (int i = 1; i <= n; i++) {
        if (!in[i])
            cout << "1 " << i << "\n";
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
