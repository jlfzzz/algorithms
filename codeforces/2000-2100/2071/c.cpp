#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, s, e;
    cin >> n >> s >> e;
    vector adj(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v), adj[v].push_back(u);
    }
    vector dis(n + 1, vector<int>());
    vector<int> d(n + 1);
    auto dfs = [&](auto &&self, int v, int par) -> void {
        d[v] = d[par] + 1;
        dis[d[v]].push_back(v);
        for (int u: adj[v]) {
            if (u == par)
                continue;
            self(self, u, v);
        }
    };
    dfs(dfs, e, 0);
    for (int i = n; i >= 1; i--) {
        for (int j: dis[i]) {
            cout << j << " ";
        }
    }
    cout << "\n";
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
