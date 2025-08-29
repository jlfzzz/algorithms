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
    vector<vector<int>> g(n + 1, vector<int>());
    For(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> dfn(n + 1), low(n + 1), cut(n + 1);
    int timestamp = 0;

    auto tarjan = [&](this auto &&tarjan, int u, int fa) -> void {
        dfn[u] = low[u] = ++timestamp;
        int child = 0;
        for (int v: g[u]) {
            if (v == fa)
                continue;
            if (!dfn[v]) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (fa != -1 && low[v] >= dfn[u])
                    cut[u] = 1;
                child++;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (fa == -1 && child > 1)
            cut[u] = 1;
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, -1);
        }
    }

    vector<int> res;
    for (int i = 1; i <= n; i++)
        if (cut[i])
            res.push_back(i);
    cout << res.size() << '\n';
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << (i + 1 == res.size() ? '\n' : ' ');
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
