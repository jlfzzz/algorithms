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
    int n, t;
    cin >> n >> t;
    vector<vector<int>> g(n + 1, vector<int>());
    For(i, n - 1) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<pii> dp(n + 1);
    auto dfs1 = [&](this auto &&dfs1, int u, int fa) -> void {
        dp[u].second = 1;
        for (int v: g[u]) {
            if (v != fa) {
                dfs1(v, u);
                auto [a, b] = dp[v];
                dp[u].second &= a;
                dp[u].first |= b;
            }
        }
    };

    dfs1(1, -1);

    vector<bool> ans(n + 1);
    auto dfs2 = [&](this auto &&dfs2, int u, int fa) -> void {
        int cnt0 = 0, cnt1 = 0;
        for (int v: g[u]) {
            if (dp[v].first) {
                cnt0++;
            } else {
                cnt1++;
            }
        }

        if (cnt1) {
            ans[u] = true;
            dp[u].first = 1;
            dp[u].second = 0;
        } else {
            dp[u].second = 1;
            dp[u].first = 0;
        }

        pii old = {dp[u].first, dp[u].second};
        for (int v: g[u]) {
            if (v != fa) {
                if (cnt1 == 1 && dp[v].second) {
                    dp[u].first = 0;
                }

                if (cnt0 == 1 && dp[v].first) {
                    dp[u].second = 0;
                }

                dfs2(v, u);
                dp[u] = old;
            }
        }
    };

    dfs2(1, -1);

    For(i, t) {
        int start;
        cin >> start;

        if (ans[start]) {
            cout << "Ron\n";
        } else {
            cout << "Hermione\n";
        }
    }
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
