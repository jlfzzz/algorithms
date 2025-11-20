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
    vector<int> temp;
    vector<vector<int>> g(n + 1);
    For(i, n) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(i + 1);
        g[b].push_back(i + 1);

        if (a == 0 && b == 0) {
            temp.push_back(i + 1);
        }
    }

    int ans = 0;
    vector<int> vis(n + 1);
    auto dfs = [&](auto &&dfs, int u) -> void {
        ans++;
        vis[u] = 1;
        for (int v: g[u]) {
            if (!vis[v]) {
                dfs(dfs, v);
            }
        }
    };

    for (int x: temp) {
        dfs(dfs, x);
    }

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
