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
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> g(n + 1, vector<int>());
    vector<int> deg(n + 1);
    For(i, m) {
        int u, v;
        cin >> u >> v;
        // 反图
        g[v].push_back(u);
        deg[u]++;
    }

    vector<pii> dp(n + 1, {1, 1});
    deque<int> dq;

    while (q--) {
        int x, u;
        cin >> x >> u;

        if (x == 1) {
            if (dp[u].first)
                dp[u].first = 0;
            if (dp[u].second) {
                dp[u].second = 0;
                dq.push_back(u);
            }
            deg[u] = 0;
            for (int v: g[u]) {
                if (dp[v].second) {
                    dp[v].second = 0;
                    dq.push_back(v);
                }
            }

            while (!dq.empty()) {
                int node = dq.front();
                dq.pop_front();

                for (int v: g[node]) {
                    if (deg[v] > 0 && dp[v].first) {
                        deg[v]--;
                        if (deg[v] == 0 && dp[v].first) {
                            dp[v].first = 0;
                            for (int w: g[v]) {
                                if (dp[w].second) {
                                    dp[w].second = 0;
                                    dq.push_back(w);
                                }
                            }
                        }
                    }
                }
            }
        } else {
            cout << (dp[u].first ? "YES" : "NO") << '\n';
        }
    }
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
