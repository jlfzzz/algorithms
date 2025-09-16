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
    vector<int> happy(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> happy[i];

    vector<vector<int>> g(n + 1);
    vector<int> has_parent(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int l, k;
        cin >> l >> k;
        g[k].push_back(l);
        has_parent[l] = 1;
    }

    vector<array<int, 2>> dp(n + 1, {0, 0});

    auto dfs = [&](auto &&self, int u) -> void {
        dp[u][1] = happy[u];
        dp[u][0] = 0;
        for (int v: g[u]) {
            self(self, v);
            dp[u][1] += dp[v][0];
            dp[u][0] += max(dp[v][0], dp[v][1]);
        }
    };

    int root = 0;
    for (int i = 1; i <= n; i++)
        if (!has_parent[i])
            root = i;

    dfs(dfs, root);

    cout << max(dp[root][0], dp[root][1]) << "\n";
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
