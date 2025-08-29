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
    vector g(n + 1, vector<int>());
    For(i, n) {
        int t;
        cin >> t;
        while (t != 0) {
            g[i + 1].push_back(t);
            cin >> t;
        }
    }

    vector<int> dfn(n + 1), low(n + 1), in_stack(n + 1);
    vector<int> scc(n + 1);
    int scc_cnt = 0, timestamp = 0;
    stack<int> stk;

    auto tarjan = [&](this auto &&tarjan, int u) -> void {
        dfn[u] = low[u] = ++timestamp;
        stk.emplace(u), in_stack[u] = 1;

        for (int v: g[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u]) {
            scc_cnt++;
            while (true) {
                int x = stk.top();
                stk.pop();
                in_stack[x] = 0;
                scc[x] = scc_cnt;
                if (x == u) {
                    break;
                }
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    vector<int> in(scc_cnt + 1), out(scc_cnt + 1);

    for (int i = 1; i <= n; i++) {
        for (int v: g[i]) {
            if (scc[i] != scc[v]) {
                in[scc[v]]++;
                out[scc[i]]++;
            }
        }
    }
    int a = 0, b = 0;
    for (int i = 1; i <= scc_cnt; i++) {
        if (!in[i]) {
            a++;
        }

        if (!out[i]) {
            b++;
        }
    }

    cout << a << '\n';

    if (scc_cnt == 1) {
        cout << 0 << '\n';
    } else {
        cout << max(a, b) << '\n';
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
