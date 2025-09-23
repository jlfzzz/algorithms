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

    vector<map<int, int>> g(n + 1);
    For(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        if (!g[u].contains(v)) {
            g[u][v] = w;
        } else {
            g[u][v] = min(g[u][v], w);
        }
        if (!g[v].contains(u)) {
            g[v][u] = w;
        } else {
            g[v][u] = min(g[v][u], w);
        }
    }

    vector<int> slowness(n + 1);
    For(i, n) cin >> slowness[i + 1];

    int mx = ranges::max(slowness);

    vector<vector<int>> dis(n + 1, vector<int>(mx + 1, inf));
    dis[1][slowness[1]] = 0;

    struct Info {
        int d, u, mn;
    };

    struct cmp {
        bool operator()(const Info &a, const Info &b) const { return a.d > b.d; }
    };

    priority_queue<Info, vector<Info>, cmp> pq;
    pq.emplace(0, 1, slowness[1]);
    while (!pq.empty()) {
        auto [d, u, mn] = pq.top();
        pq.pop();

        if (d > dis[u][mn]) {
            continue;
        }

        if (u == n) {
            cout << d << endl;
            return;
        }

        // cout << "d is :" << d << endl;
        for (auto &[v, w]: g[u]) {
            int nd = d + w * mn;
            int nmn = min(mn, slowness[v]);
            if (nd < dis[v][nmn]) {
                dis[v][nmn] = nd;
                pq.emplace(nd, v, nmn);
            }
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
