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
    For(i, m) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }

    vector<int> dfn(n + 1), in_stack(n + 1), low(n + 1), scc(n + 1), scc_sz(n + 1);
    int cnt = 0, timestamp = 0;
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

        if (low[u] == dfn[u]) {
            ++cnt;
            int sz = 0;
            while (true) {
                int x = stk.top();
                stk.pop();
                scc[x] = cnt;
                sz++;
                if (x == u) {
                    break;
                }
            }
            scc_sz[cnt] = sz;
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    set<pii> edges;
    for (int i = 1; i <= n; i++) {
        for (int v: g[i]) {
            int s1 = scc[i], s2 = scc[v];
            if (s1 != s2) {
                edges.emplace(s1, s2);
            }
        }
    }

    vector<int> out(cnt + 1);
    for (auto &[from, to]: edges) {
        out[from]++;
    }

    int sink_cnt = 0, sink_id = -1;
    for (int i = 1; i <= cnt; i++) {
        if (out[i] == 0) {
            sink_cnt++;
            sink_id = i;
        }
    }

    int ans = 0;
    if (sink_cnt == 1)
        ans = scc_sz[sink_id];

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
