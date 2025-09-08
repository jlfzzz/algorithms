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
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back((int) v);
        g[v].push_back((int) u);
    }
    vector<int> tin(n + 1), tout(n + 1), sz(n + 1);
    int ts = 0;
    auto dfs = [&](this auto &&dfs, int u, int p) -> void {
        tin[u] = ++ts;
        sz[u] = 1;
        for (int v: g[u])
            if (v != p) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        tout[u] = tin[u] + sz[u] - 1;
    };
    dfs(1, 0);

    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> p[i];

    struct Info {
        int x, id, sign;
    };
    vector<vector<Info>> ev(n + 1);
    for (int i = 0; i < q; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        ev[r].push_back({x, i, 1});
        if (l - 1 >= 0)
            ev[l - 1].push_back({x, i, -1});
    }

    vector<int> bit(n + 2, 0), ans(q, 0);
    auto add = [&](int idx, int val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    };
    auto query = [&](int idx) {
        int s = 0;
        for (; idx > 0; idx -= idx & -idx)
            s += bit[idx];
        return s;
    };

    for (int k = 0; k <= n; ++k) {
        if (k >= 1)
            add(tin[p[k]], 1);
        for (auto &e: ev[k]) {
            int cnt = query(tout[e.x]) - query(tin[e.x] - 1);
            ans[e.id] += e.sign * cnt;
        }
    }

    for (int i = 0; i < q; ++i)
        cout << (ans[i] > 0 ? "YES\n" : "NO\n");
}

struct Node {
    int val = 0;
};

class PST {
private:
    int n, ts;
    std::vector<int> lc, rc;
    std::vector<Node> tree;

    void newnode(int pre, int cur) {
        lc[cur] = lc[pre];
        rc[cur] = rc[pre];
        tree[cur] = tree[pre];
    }

    Node merge(const Node &left, const Node &right) { return Node{left.val + right.val}; }

    int _build(const std::vector<int> &arr, int l, int r) {
        int cur = ++ts;
        if (l == r) {
            tree[cur] = Node{arr[l]};
            return cur;
        }
        int m = (l + r) / 2;
        lc[cur] = _build(arr, l, m);
        rc[cur] = _build(arr, m + 1, r);
        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    int _update(int pre, int l, int r, int pos, int val) {
        int cur = ++ts;
        newnode(pre, cur);
        if (l == r) {
            tree[cur].val += val;
            return cur;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            lc[cur] = _update(lc[pre], l, m, pos, val);
        else
            rc[cur] = _update(rc[pre], m + 1, r, pos, val);

        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    int _query(int cur, int pre, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;
        if (ql <= l && r <= qr)
            return tree[cur].val - tree[pre].val;
        int m = (l + r) / 2;
        return _query(lc[cur], lc[pre], l, m, ql, qr) + _query(rc[cur], rc[pre], m + 1, r, ql, qr);
    }

    int _kth(int cur, int pre, int l, int r, int k) {
        if (l == r)
            return l;
        int cnt = tree[lc[cur]].val - tree[lc[pre]].val;
        int m = (l + r) / 2;
        if (k <= cnt)
            return _kth(lc[cur], lc[pre], l, m, k);
        else
            return _kth(rc[cur], rc[pre], m + 1, r, k - cnt);
    }

public:
    std::vector<int> root;

    PST(int n) : n(n), ts(0), lc(22 * n + 5), rc(22 * n + 5), tree(22 * n + 5), root(22 * n + 5) {}

    int build(const std::vector<int> &arr) { return _build(arr, 1, n); }

    int update(int pre_version, int pos, int val) { return _update(pre_version, 1, n, pos, val); }

    int query(int cur_version, int pre_version, int l, int r) { return _query(cur_version, pre_version, 1, n, l, r); }

    int kth(int cur_version, int pre_version, int k) { return _kth(cur_version, pre_version, 1, n, k); }
};


void solve() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n + 1);
    For(i, n - 1) {
        int u, v;
        cin >> u >> v;
        g[u].push_back((int) v);
        g[v].push_back((int) u);
    }
    vector<int> tin(n + 1), tout(n + 1), sz(n + 1);
    int ts = 0;
    auto dfs = [&](this auto &&dfs, int u, int p) -> void {
        tin[u] = ++ts;
        sz[u] = 1;
        for (int v: g[u])
            if (v != p) {
                dfs(v, u);
                sz[u] += sz[v];
            }
        tout[u] = tin[u] + sz[u] - 1;
    };
    dfs(1, 0);

    PST pst(n + 10);
    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        pst.root[i] = pst.update(pst.root[i - 1], tin[p], 1);
    }

    while (q--) {
        int l, r, x;
        cin >> l >> r >> x;

        int cnt = pst.query(pst.root[r], pst.root[l - 1], tin[x], tout[x]);
        cout << ((cnt > 0) ? "YES\n" : "NO\n");
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
