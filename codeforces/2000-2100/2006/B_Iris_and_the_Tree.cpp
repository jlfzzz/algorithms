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

void solve2() {
    int n, w;
    cin >> n >> w;

    vector<vector<int>> g(n + 1, vector<int>());
    vector<int> parent(n + 1);
    parent[1] = 0;
    For(i, n - 1) {
        int p;
        cin >> p;
        parent[i + 2] = p;
        g[p].push_back(i + 2);
    }

    vector<int> r(n + 1, 0);
    function<void(int)> dfs = [&](int u) {
        int mx = u;
        for (int v: g[u]) {
            dfs(v);
            mx = max(mx, (int) r[v]);
        }
        r[u] = mx;
    };
    dfs(1);

    vector<int> fa(n + 1), sz(n + 1, 1);
    iota(fa.begin(), fa.end(), 0);
    function<int(int)> find = [&](int x) {
        while (fa[x] != x) {
            fa[x] = fa[fa[x]];
            x = fa[x];
        }
        return x;
    };
    auto unite = [&](int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        fa[b] = a;
        sz[a] += sz[b];
        return true;
    };

    auto nxt = [&](int x) { return x == n ? 1 : x + 1; };
    auto prv = [&](int x) { return x == 1 ? n : x - 1; };

    int c = n;
    int S = 0;

    For(qi, n - 1) {
        int x, y;
        cin >> x >> y;

        int rx = find(x);
        int rp = find(parent[x]);
        int cnt = 0;

        if (find(prv(x)) == rp)
            cnt += 1;
        if (find(r[x]) == rx && find(nxt(r[x])) == rp)
            cnt += 1;
        unite(rx, rp);
        c -= cnt;


        S += y;
        int W = w - S;
        cout << (2 * S + c * W) << (qi + 1 == n - 1 ? '\n' : ' ');
    }
}

class LcaBinaryLifting {
public:
    vector<int> depth;
    vector<ll> dis;
    vector<vector<int>> pa;
    vector<vector<pair<int, int>>> g;
    int N, LOG;

    LcaBinaryLifting(int n, vector<vector<int>> &edges) {
        N = n;
        LOG = bit_width((unsigned) (N + 1));
        g.assign(N + 1, {});
        for (auto &e: edges) {
            int x = e[0], y = e[1], w = e[2];
            g[x].emplace_back(y, w);
            g[y].emplace_back(x, w);
        }
        depth.assign(N + 1, 0);
        dis.assign(N + 1, 0);
        pa.assign(N + 1, vector<int>(LOG, -1));

        dfs(1, -1);

        for (int j = 0; j + 1 < LOG; ++j) {
            for (int v = 1; v <= N; ++v) {
                if (pa[v][j] != -1)
                    pa[v][j + 1] = pa[pa[v][j]][j];
            }
        }
    }

    void dfs(int x, int fa) {
        pa[x][0] = fa;
        for (auto &ew: g[x]) {
            int y = ew.first, w = ew.second;
            if (y == fa)
                continue;
            depth[y] = depth[x] + 1;
            dis[y] = dis[x] + w;
            dfs(y, x);
        }
    }

    int get_kth_ancestor(int node, int k) {
        for (int i = 0; i < LOG && node != -1; ++i) {
            if (k >> i & 1) {
                node = pa[node][i];
            }
        }
        return node;
    }

    int get_lca(int x, int y) {
        if (depth[x] > depth[y])
            swap(x, y);
        y = get_kth_ancestor(y, depth[y] - depth[x]);
        if (x == y)
            return x;
        for (int i = LOG - 1; i >= 0; --i) {
            if (pa[x][i] != pa[y][i]) {
                x = pa[x][i];
                y = pa[y][i];
            }
        }
        return pa[x][0];
    }

    ll get_dis(int x, int y) {
        int l = get_lca(x, y);
        return dis[x] + dis[y] - 2 * dis[l];
    }
};

void solve() {
    int n, w;
    cin >> n >> w;

    vector<vector<int>> g(n + 1, vector<int>());
    vector<vector<int>> edges;
    vector<int> parent(n + 1);
    parent[1] = 0;
    For(i, n - 1) {
        int p;
        cin >> p;
        parent[i + 2] = p;
        g[p].push_back(i + 2);
        g[i + 2].push_back(p);

        vector<int> temp{p, i + 2, 1};
        edges.emplace_back(temp);
    }

    LcaBinaryLifting lca(n, edges);

    auto nxt = [&](int x) { return x == n ? 1 : x + 1; };
    auto prv = [&](int x) { return x == 1 ? n : x - 1; };

    vector<int> len(n + 1), cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        len[i] = lca.get_dis(i, nxt(i));
    }

    vector<int> r(n + 1);
    auto dfs = [&](this auto &&dfs, int u, int fa) -> int {
        int mx = u;
        for (int v: g[u]) {
            if (v != fa) {
                mx = max(mx, dfs(v, u));
            }
        }
        r[u] = mx;
        return mx;
    };
    dfs(1, -1);

    int ans = n * w;
    int all = 0;
    int unfilled = n;

    auto calc = [&](int i) {
        if (len[i] == 0) {
            return cnt[i];
        }

        return w - all + cnt[i];
    };

    For(_, n - 1) {
        int x, y;
        cin >> x >> y;

        int px = prv(x);
        ans -= calc(px);
        ans -= calc(r[x]);

        bool a = (len[px] > 0);
        bool b = (len[r[x]] > 0);
        ans -= y * (unfilled - (a ? 1 : 0) - (b ? 1 : 0));

        if (len[px] > 0 && --len[px] == 0)
            unfilled--;
        if (len[r[x]] > 0 && --len[r[x]] == 0)
            unfilled--;

        all += y;
        cnt[px] += y;
        cnt[r[x]] += y;

        ans += calc(px);
        ans += calc(r[x]);

        cout << ans << ' ';
    }

    cout << '\n';
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
