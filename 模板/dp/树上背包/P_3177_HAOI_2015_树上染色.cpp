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

// int n, k;
// vector<vector<pii>> g;
// vector<int> sz;

// vector<int> dfs(int u, int p) {
//     vector<int> dp(2, 0);
//     sz[u] = 1;
//     for (auto &e: g[u]) {
//         int v = e.first, w = e.second;
//         if (v == p)
//             continue;
//         auto ch = dfs(v, u);
//         int lim_u = (int) dp.size() - 1;
//         int lim_v = (int) ch.size() - 1;
//         int new_lim = min(k, lim_u + lim_v);
//         vector<int> ndp(new_lim + 1, -inf);
//         for (int t = 0; t <= min(k, lim_u); ++t) {
//             if (dp[t] <= -inf / 4)
//                 continue;
//             int up = min(lim_v, k - t);
//             for (int j = 0; j <= up; ++j) {
//                 if (ch[j] <= -inf / 4)
//                     continue;
//                 int add = w * (j * (k - j) + (sz[v] - j) * ((n - k) - (sz[v] - j)));
//                 ndp[t + j] = max(ndp[t + j], dp[t] + ch[j] + add);
//             }
//         }
//         dp.swap(ndp);
//         sz[u] += sz[v];
//     }
//     if ((int) dp.size() > k + 1)
//         dp.resize(k + 1);
//     return dp;
// }
// cin >> n >> k;
// g.assign(n + 1, {});
// for (int i = 1; i <= n - 1; ++i) {
//     int u, v, w;
//     cin >> u >> v >> w;
//     g[u].push_back({v, w});
//     g[v].push_back({u, w});
// }
// sz.assign(n + 1, 0);
// auto res = dfs(1, 0);
// cout << res[k] << '\n';
void init() {}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<vector<pii>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<vector<int>> dp(n + 1, vector<int>(k + 1, -inf));
    vector<int> sz(n + 1, 0);

    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        sz[u] = 1;
        dp[u][0] = 0; // 选择0个节点的价值
        dp[u][1] = 0; // 选择1个节点的价值（根据具体问题调整）

        for (const auto &[v, w]: g[u]) {
            if (v == fa)
                continue;

            dfs(v, u); // 先递归处理子节点

            // 临时数组用于背包合并
            vector<int> temp(dp[u].begin(), dp[u].end());

            // 背包合并：从大到小遍历避免重复计算
            for (int i = min(k, sz[u]); i >= 0; i--) {
                if (dp[u][i] == -inf)
                    continue;

                for (int j = min(k - i, sz[v]); j >= 0; j--) {
                    if (dp[v][j] == -inf)
                        continue;

                    // 计算边(u,v)的贡献
                    int add = w * (j * (k - j) + (sz[v] - j) * (n - k - (sz[v] - j)));
                    temp[i + j] = max(temp[i + j], dp[u][i] + dp[v][j] + add);
                }
            }

            dp[u] = std::move(temp);
            sz[u] += sz[v];
        }
    };

    dfs(1, 0);
    cout << dp[1][k] << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
