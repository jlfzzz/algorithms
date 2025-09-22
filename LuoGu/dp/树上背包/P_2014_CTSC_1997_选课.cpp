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

    vector<vector<int>> g(n + 1);
    vector<int> values(n + 1);
    For(i, n) {
        int k, s;
        cin >> k >> s;
        g[k].push_back(i + 1);
        values[i + 1] = s;
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 2, -1));
    auto dfs = [&](this auto &&dfs, int u) -> void {
        dp[u][0] = 0;
        dp[u][1] = values[u];
        for (int v: g[u]) {
            dfs(v);
            vector<int> ndp(m + 2, -1);
            ndp[0] = 0;
            for (int j = 1; j <= m + 1; j++) {
                if (dp[u][j] != -1)
                    ndp[j] = max(ndp[j], dp[u][j]);
                for (int k = 0; k <= j - 1; k++) {
                    if (dp[u][j - k] == -1 || dp[v][k] == -1)
                        continue;
                    ndp[j] = max(ndp[j], dp[u][j - k] + dp[v][k]);
                }
            }
            dp[u].swap(ndp);
        }
    };

    values[0] = 0;
    dfs(0);

    cout << dp[0][m + 1] << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
