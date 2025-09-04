#include <bits/stdc++.h>
#include <vector>
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

/*
    HLD 中 pos 是点的编号，根据dfs序
        base 是在线段树里面的下标
*/


struct SegmentTreeNode {
    ll val, lazy;
    SegmentTreeNode(ll v = 0, ll lz = 0) : val(v), lazy(lz) {}
};

class SegmentTree {
private:
    int n;
    vector<SegmentTreeNode> tree;

    void apply(int node, int l, int r, ll val) {
        tree[node].val += val * (r - l + 1);
        tree[node].lazy += val;
    }

    void pushDown(int node, int l, int r) {
        if (tree[node].lazy != 0) {
            int mid = (l + r) / 2;
            apply(node * 2, l, mid, tree[node].lazy);
            apply(node * 2 + 1, mid + 1, r, tree[node].lazy);
            tree[node].lazy = 0;
        }
    }

    void build(const vector<ll> &nums, int node, int l, int r) {
        if (l == r) {
            tree[node] = {nums[l], 0};
            return;
        }
        int mid = (l + r) / 2;
        build(nums, node * 2, l, mid);
        build(nums, node * 2 + 1, mid + 1, r);
        tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
    }

    void update(int node, int l, int r, int idx, ll val) {
        if (l == r) {
            tree[node].val += val;
            return;
        }
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);
        tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
    }

    void rangeAdd(int node, int l, int r, int ql, int qr, ll val) {
        if (qr < l || r < ql)
            return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        rangeAdd(node * 2, l, mid, ql, qr, val);
        rangeAdd(node * 2 + 1, mid + 1, r, ql, qr, val);
        tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tree[node].val;
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        return query(node * 2, l, mid, ql, qr) + query(node * 2 + 1, mid + 1, r, ql, qr);
    }

public:
    explicit SegmentTree(const vector<ll> &nums) {
        n = nums.size();
        tree.resize(4 * n);
        build(nums, 1, 0, n - 1);
    }

    explicit SegmentTree(int n) : n(n) { tree.resize(4 * n); }

    void build(vector<ll> &nums) { build(nums, 1, 0, n - 1); }

    void update(int idx, ll val) { update(1, 0, n - 1, idx, val); }

    void rangeAdd(int l, int r, ll val) { rangeAdd(1, 0, n - 1, l, r, val); }

    ll rangeSum(int l, int r) { return query(1, 0, n - 1, l, r); }

    ll getValue(int idx) { return rangeSum(idx, idx); }
};

class HLD {
public:
    int n, timer{};
    vector<vector<ll>> g;
    vector<ll> depth, parent, heavy, head, pos, sz;
    vector<ll> val, base;
    SegmentTree st;

    explicit HLD(int n) : n(n), st(4 * n) { init(n); }

    void init(int _n) {
        n = _n;
        timer = 0;
        g.resize(n + 1);
        parent.resize(n + 1);
        depth.resize(n + 1);
        heavy.resize(n + 1);
        head.resize(n + 1);
        pos.resize(n + 1);
        sz.resize(n + 1);
        val.resize(n + 1);
        base.resize(n + 1);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ll dfs1(int u, int fa) {
        sz[u] = 1;
        parent[u] = fa;
        heavy[u] = -1;
        depth[u] = depth[fa] + 1;
        for (int v: g[u]) {
            if (v == fa)
                continue;
            sz[u] += dfs1(v, u);
            if (heavy[u] == -1 || sz[v] > sz[heavy[u]])
                heavy[u] = v;
        }
        return sz[u];
    }

    void dfs2(int u, int top) {
        head[u] = top;
        pos[u] = ++timer;
        base[pos[u]] = val[u];
        if (heavy[u] != -1)
            dfs2(heavy[u], top);
        for (int v: g[u]) {
            if (v == parent[u] || v == heavy[u])
                continue;
            dfs2(v, v);
        }
    }

    void build(int root) {
        depth[root] = 0;
        dfs1(root, -1);
        dfs2(root, root);
        st.build(base);
    }

    ll path_sum(int u, int v) {
        ll res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            res += st.rangeSum(pos[head[u]], pos[u]);
            u = parent[head[u]];
        }
        if (depth[u] < depth[v])
            swap(u, v);
        res += st.rangeSum(pos[v], pos[u]);
        return res;
    }

    void path_add(int u, int v, ll val) {
        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            st.rangeAdd(pos[head[u]], pos[u], val);
            u = parent[head[u]];
        }
        if (depth[u] < depth[v])
            swap(u, v);
        st.rangeAdd(pos[v], pos[u], val);
    }

    ll subtree_sum(int u) { return st.rangeSum(pos[u], pos[u] + sz[u] - 1); }

    void subtree_add(int u, ll val) { st.rangeAdd(pos[u], pos[u] + sz[u] - 1, val); }

    void update(int u, ll val) { st.update(pos[u], val); }
};

void solve() {
    int n, m, r, p;
    cin >> n >> m >> r >> p;

    vector<int> values(n + 1);
    HLD hld(n);

    For(i, n) cin >> values[i + 1];
    For(i, n + 1) hld.val[i] = values[i];

    For(i, n - 1) {
        int x, y;
        cin >> x >> y;
        hld.add_edge(x, y);
    }

    hld.build(r);

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, z;
            cin >> x >> y >> z;
            hld.path_add(x, y, z);
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;
            cout << hld.path_sum(x, y) % p << '\n';
        } else if (op == 3) {
            int x, y;
            cin >> x >> y;
            hld.subtree_add(x, y);
        } else if (op == 4) {
            int x;
            cin >> x;
            cout << hld.subtree_sum(x) % p << '\n';
        }
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
