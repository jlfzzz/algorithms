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
    vector<int> weights(n + 1);
    For(i, n) { cin >> weights[i + 1]; }
    For(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    vector<int> dfn(n + 1), low(n + 1), in(n + 1), scc_weights(n + 1), scc(n + 1);
    stack<int> stk;
    int timestamp = 0, cnt = 0;

    auto tarjan = [&](this auto &&tarjan, int u) -> void {
        dfn[u] = low[u] = ++timestamp;
        stk.emplace(u), in[u] = 1;
        for (int v: g[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            int s = 0;
            cnt++;
            while (true) {
                int x = stk.top();
                stk.pop();
                s += weights[x];
                scc[x] = cnt;
                in[x] = 0;
                if (x == u) {
                    break;
                }
            }
            scc_weights[cnt] = s;
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    // vector<set<int>> g2(cnt + 1, set<int>());
    // for (int i = 1; i <= n; i++) {
    //     for (int v: g[i]) {
    //         int c1 = scc[i], c2 = scc[v];
    //         if (c1 != c2) {
    //             g2[c1].insert(c2);
    //         }
    //     }
    // }

    // vector<int> memo(cnt + 1, -1);

    // auto dfs = [&](this auto &&dfs, int i) -> int {
    //     int res = 0;
    //     if (memo[i] != -1) {
    //         return memo[i];
    //     }
    //     for (int v: g2[i]) {
    //         res = max(res, dfs(v));
    //     }

    //     res += scc_weights[i];
    //     memo[i] = res;
    //     return res;
    // };

    // int ans = 0;
    // for (int i = 1; i <= cnt; i++) {
    //     ans = max(ans, dfs(i));
    // }

    // cout << ans << '\n';

    set<pii> edges;
    for (int i = 1; i <= n; i++) {
        for (int v: g[i]) {
            int c1 = scc[i], c2 = scc[v];
            if (c1 != c2)
                edges.emplace(c1, c2);
        }
    }

    vector<vector<int>> dag(cnt + 1);
    vector<int> indeg(cnt + 1);
    for (auto &[u, v]: edges) {
        dag[u].push_back(v);
        indeg[v]++;
    }

    vector<int> dp(cnt + 1, 0);
    queue<int> q;
    for (int i = 1; i <= cnt; i++) {
        if (indeg[i] == 0) {
            dp[i] = scc_weights[i];
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: dag[u]) {
            if (dp[v] < dp[u] + scc_weights[v])
                dp[v] = dp[u] + scc_weights[v];
            if (--indeg[v] == 0)
                q.push(v);
        }
    }
    int ans = 0;
    for (int i = 1; i <= cnt; i++)
        ans = max(ans, dp[i]);
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
