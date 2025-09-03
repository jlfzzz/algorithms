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
int fac[200'005];

void init() {
    fac[0] = 1;
    for (int i = 1; i <= 200'005; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1, vector<int>());
    vector<int> vis(n + 1);
    For(i, m) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if (n == 2) {
        cout << 2 << '\n';
        return;
    }

    int start = -1;
    int ans = 1;
    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        int cnt1 = 0;
        int cnt2 = 0;
        vis[u] = 1;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            if (vis[v]) {
                ans = 0;
                return;
            }

            if (g[v].size() > 1) {
                dfs(v, u);
                cnt1++;
            } else {
                cnt2++;
            }
        }
        if (cnt1 > 1 && u != start) {
            ans = 0;
            return;
        }

        if (cnt1 > 2) {
            ans = 0;
            return;
        }

        if (u == start && cnt1 >= 1) {
            ans = 2 * ans % MOD;
        }

        ans = ans * fac[cnt2] % MOD;
    };


    for (int i = 1; i <= n; i++) {
        if (g[i].size() > 1) {
            start = i;
            dfs(i, -1);
            break;
        }
    }

    ans = 2 * ans % MOD;
    cout << ans << '\n';
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
