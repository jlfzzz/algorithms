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


int pow2[200'005];
void init() {
    pow2[0] = 1;
    for (int i = 1; i < 200005; i++) {
        pow2[i] = 2 * pow2[i - 1] % MOD;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> deg(n + 1);
    vector<vector<int>> g(n + 1, vector<int>());
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[v]++, deg[u]++;
    }

    int cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (deg[i] == 1) {
            cnt++;
        }
    }

    if (cnt > 2) {
        cout << 0 << '\n';
        return;
    }

    if (cnt == 1) {
        cout << pow2[n] << '\n';
        return;
    }

    vector<int> dep(n + 1), father(n + 1);
    auto dfs = [&](this auto &&dfs, int i, int fa, int d) -> void {
        father[i] = fa;
        dep[i] = d;

        for (int v: g[i]) {
            if (v != fa) {
                dfs(v, i, d + 1);
            }
        }
    };

    dfs(1, -1, 1);
    int lca;
    if (deg[1] == 2) {
        lca = 1;
    } else {
        for (int i = 2; i <= n; i++) {
            if (deg[i] == 3) {
                lca = i;
            }
        }
    }

    int leaf1 = -1, leaf2 = -1;
    for (int i = 2; i <= n; i++) {
        if (deg[i] == 1) {
            if (leaf1 == -1) {
                leaf1 = i;
            } else {
                leaf2 = i;
            }
        }
    }

    int ans = 0;
    if (dep[leaf1] == dep[leaf2]) {
        ans = 2 * pow2[dep[lca]];
    } else {
        int d = dep[lca];
        int mn = min(dep[leaf1] - d, dep[leaf2] - d);
        int mx = max(dep[leaf2], dep[leaf1]);
        ans = pow2[mx - mn];

        ans += pow2[mx - mn - 1];
    }
    cout << ans % MOD << '\n';
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
