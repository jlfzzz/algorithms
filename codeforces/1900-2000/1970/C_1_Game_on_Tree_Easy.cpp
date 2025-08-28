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
    int n, t;
    cin >> n >> t;


    vector<vector<int>> g(n + 1, vector<int>());
    vector<int> deg(n + 1);

    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[v]++, deg[u]++;
    }
    int start;
    cin >> start;

    int leaf1 = -1, leaf2 = -1;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) {
            if (leaf1 == -1) {
                leaf1 = i;
            } else {
                leaf2 = i;
            }
        }
    }

    vector<int> dis(n + 1);
    dis[start] = 0;
    auto dfs = [&](this auto &&dfs, int i, int fa, int d) -> void {
        dis[i] = d;
        for (int v: g[i]) {
            if (v != fa) {
                dfs(v, i, d + 1);
            }
        }
    };
    dfs(start, -1, 0);
    int d1 = dis[leaf1], d2 = dis[leaf2];

    if (leaf1 == start) {
        if (d2 & 1) {
            cout << "Ron\n";
        } else {
            cout << "Hermione\n";
        }
    } else if (leaf2 == start) {
        if (d1 & 1) {
            cout << "Ron\n";
        } else {
            cout << "Hermione\n";
        }
    } else {
        if (d1 & 1 || d2 & 1) {
            cout << "Ron\n";
        } else {
            cout << "Hermione\n";
        }
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
