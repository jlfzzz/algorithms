#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr long long inf = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> w[i];
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<int>> f(n + 1, vector<int>(n + 1, inf));
    for (int j = 0; j <= n; j++) {
        f[1][j] = j * w[1];
    }

    for (int j = n - 1; j >= 0; j--) {
        for (int i = 1; i <= n; i++) {
            for (int u: g[i]) {
                if (f[u][j + 1] < inf) {
                    f[i][j] = min(f[i][j], f[u][j + 1] + j * w[i]);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << f[i][0] << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--)
        solve();
    return 0;
}
