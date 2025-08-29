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


    int start;
    cin >> start;
    dfs1(start, -1);

    cout << (dp[start].first ? "Ron\n" : "Hermione\n");
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
