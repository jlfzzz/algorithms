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
    vector<vector<int>> g(n + 1);
    For(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    int cnt = 0;
    int timestamp = 0;
    vector<int> dfn(n + 1), low(n + 1), in_stack(n + 1);
    stack<int> stk;

    function<void(int)> tarjan = [&](int u) {
        dfn[u] = low[u] = ++timestamp;
        stk.push(u);
        in_stack[u] = true;

        for (int v: g[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            vector<int> scc;
            while (true) {
                int x = stk.top();
                stk.pop();
                in_stack[x] = false;
                scc.push_back(x);
                if (x == u)
                    break;
            }
            if (scc.size() > 1) {
                cnt++;
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    cout << cnt << '\n';
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
