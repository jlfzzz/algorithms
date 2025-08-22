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
    int n, m;
    cin >> n >> m;

    vector g(n + 1, vector<int>());
    For(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> disc(n + 1, -1), low(n + 1, -1);
    vector<int> subtree_size(n + 1, 0);
    vector<bool> vis(n + 1, false);
    vector<pair<pii, int>> bridges;
    int timer = 0;

    auto tarjan = [&](this auto &&tarjan, int u, int p) -> int {
        vis[u] = true;
        disc[u] = low[u] = ++timer;
        subtree_size[u] = 1;

        for (int v: g[u]) {
            if (v == p)
                continue;

            if (!vis[v]) {
                int child_size = tarjan(v, u);
                subtree_size[u] += child_size;

                low[u] = min(low[u], low[v]);

                if (low[v] > disc[u]) {
                    bridges.push_back({{u, v}, child_size});
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }

        return subtree_size[u];
    };

    tarjan(1, -1);

    int totalPairs = n * (n - 1) / 2;

    if (bridges.empty()) {
        cout << totalPairs << "\n";
        return;
    }

    int ans = inf;

    for (auto &bridge: bridges) {
        int size1 = bridge.second;
        int size2 = n - size1;

        int remainingPairs = size1 * (size1 - 1) / 2 + size2 * (size2 - 1) / 2;

        ans = min(ans, remainingPairs);
    }

    cout << ans << "\n";
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
