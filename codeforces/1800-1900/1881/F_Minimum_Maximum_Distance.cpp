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
    int n, k;
    cin >> n >> k;

    vector<int> marked(n + 1);
    For(i, k) {
        int t;
        cin >> t;
        marked[t] = 1;
    }

    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> mx1(n + 1), mx2(n + 1), mx_cnt(n + 1);
    auto dfs1 = [&](this auto &&dfs1, int u, int fa) -> void {
        mx1[u] = (marked[u] ? 0 : -inf);
        mx2[u] = mx1[u];

        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            dfs1(v, u);
            if (mx1[v] + 1 > mx1[u]) {
                mx2[u] = mx1[u];
                mx1[u] = mx1[v] + 1;
                mx_cnt[u] = 1;
            } else if (mx1[v] + 1 == mx1[u]) {
                mx_cnt[u]++;
            } else if (mx1[v] + 1 > mx2[u]) {
                mx2[u] = mx1[v] + 1;
            }
        }
    };

    dfs1(1, -1);
    int ans = inf;
    auto dfs2 = [&](this auto &&dfs2, int u, int fa) -> void {
        ans = min(ans, mx1[u]);

        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            auto update = [&](int v, int val) {
                if (val > mx1[v]) {
                    mx2[v] = mx1[v];
                    mx1[v] = val;
                    mx_cnt[v] = 1;
                } else if (val == mx1[v]) {
                    mx_cnt[v]++;
                } else if (val > mx2[v]) {
                    mx2[v] = val;
                }
            };

            int from;
            if (mx1[u] == mx1[v] + 1 && mx_cnt[u] == 1) {
                from = mx2[u] + 1;
            } else {
                from = mx1[u] + 1;
            }

            update(v, from);

            dfs2(v, u);
        }
    };

    dfs2(1, -1);
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
