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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector g(n + 1, vector<int>());
    For(i, m) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int clock = 0;
    vector<int> dfn(n + 1);
    vector<int> low(n + 1);
    vector<int> children(n + 1);
    vector<pii> bridges;

    auto dfs = [&](this auto &&dfs, int i, int fa) -> int {
        int cnt = 1;
        dfn[i] = low[i] = ++clock;

        for (int v: g[i]) {
            if (v == fa) {
                continue;
            }

            if (!dfn[v]) {
                cnt += dfs(v, i);
                low[i] = min(low[i], low[v]);
                if (low[v] > dfn[i]) {
                    bridges.emplace_back(i, v);
                }
            } else {
                low[i] = min(low[i], dfn[v]);
            }
        }

        children[i] = cnt;
        return cnt;
    };

    dfs(1, -1);

    int ans = n * (n - 1) / 2;

    for (const auto &[x, y]: bridges) {
        int child_size, parent_size;
        if (dfn[x] < dfn[y]) {
            child_size = children[y];
        } else {
            child_size = children[x];
        }
        parent_size = n - child_size;
        ans = min(ans, parent_size * (parent_size - 1) / 2 + child_size * (child_size - 1) / 2);
    }
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
