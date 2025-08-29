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
    vector<vector<int>> g(n + 1, vector<int>());
    For(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> dfn(n + 1), low(n + 1), sz(n + 1);
    vector<int> ans(n + 1);
    int ts = 0;

    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        dfn[u] = low[u] = ++ts;
        sz[u] = 1;
        ll sum = 0;
        for (int v: g[u]) {
            if (v == fa)
                continue;
            if (!dfn[v]) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                sz[u] += sz[v];
                if (low[v] >= dfn[u]) {
                    ans[u] += 1LL * sz[v] * (n - 1 - sz[v]);
                    sum += sz[v];
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        ans[u] += 2LL * (n - 1);
        ans[u] += sum * (n - 1 - sum);
    };

    dfs(1, 0);

    for (int i = 1; i <= n; i++)
        cout << ans[i] << '\n';
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
