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

    vector<vector<int>> g(n + 2);
    vector<int> vals(1);
    vals.push_back(1);
    vector<vector<pii>> queries(n + 2);
    int sz = 1;
    int qid = 0;

    For(i, n) {
        char op;
        cin >> op;

        if (op == '+') {
            int v, k;
            cin >> v >> k;

            sz++;
            g[v].push_back(sz);
            vals.push_back(k);
        } else {
            int u, v, k;
            cin >> u >> v >> k;
            queries[v].emplace_back(k, qid);
            qid++;
        }
    }

    int pref = 0;
    vector<int> ans(qid);
    auto dfs = [&](this auto &&dfs, int u, int mn, int mx, int up, int down) -> void {
        pref += vals[u];
        up = max(up, pref - mn);
        down = max(down, mx - pref);
        mn = min(mn, pref);
        mx = max(mx, pref);

        for (auto &[val, id]: queries[u]) {
            if (-down <= val && val <= up)
                ans[id] = 1;
        }

        for (auto v: g[u]) {
            dfs(v, mn, mx, up, down);
        }
        pref -= vals[u];
    };

    dfs(1, 0, 0, 0, 0);

    For(i, qid) {
        if (ans[i]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
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
