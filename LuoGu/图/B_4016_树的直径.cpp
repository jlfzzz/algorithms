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
    vector<vector<int>> g(n + 1, vector<int>());
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int ans = 0;
    auto dfs = [&](this auto &&dfs, int u, int fa) -> int {
        int mx1 = 0, mx2 = 0;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            int d = dfs(v, u) + 1;
            if (d > mx1) {
                mx2 = mx1, mx1 = d;
            } else if (d > mx2) {
                mx2 = d;
            }
        }

        ans = max(ans, mx1 + mx2);
        return mx1;
    };

    dfs(1, -1);

    cout << ans << '\n';
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
