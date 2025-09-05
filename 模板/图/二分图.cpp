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


// 匈牙利算法
void solve1() {
    int n, m, e;
    cin >> n >> m >> e;

    vector<vector<int>> g(n + 1);
    For(i, e) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    int ans = 0;
    vector<int> vis(m + 1, -1), match(m + 1);

    auto dfs = [&](this auto &&dfs, int u, int root) -> bool {
        for (int v: g[u]) {
            if (vis[v] == root) {
                continue;
            }
            vis[v] = root;
            if (!match[v] || dfs(match[v], root)) {
                match[v] = u;
                return true;
            }
        }
        return false;
    };


    for (int i = 1; i <= n; i++) {
        if (dfs(i, i)) {
            ans++;
        }
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
        solve1();
    return 0;
}
