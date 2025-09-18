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

struct Node {
    int sum; // number of 1 (occupied)
    int len;
    int l0; // left consecutive 0
    int r0; // right consecutive 0
    int mx0; // max consecutive 0
    int lazy; // 0: set to 0, 1: set to 1, -1: no lazy
};

struct Seg {
    int n;
    vector<Node> tree;
    Seg(int n) : n(n), tree(8 * n + 10) {}

    Node merge(Node l, Node r) {
        Node res;
        res.len = l.len + r.len;
        res.sum = l.sum + r.sum;
        res.lazy = -1;

        // update l0
        if (l.sum == 0) { // left segment is all 0
            res.l0 = l.len + r.l0;
        } else {
            res.l0 = l.l0;
        }

        // update r0
        if (r.sum == 0) { // right segment is all 0
            res.r0 = r.len + l.r0;
        } else {
            res.r0 = r.r0;
        }

        res.mx0 = max({l.mx0, r.mx0, l.r0 + r.l0});
        return res;
    }

    void build(int o, int l, int r) {
        if (l == r) {
            tree[o] = {1, 1, 0, 0, 0, -1}; // 初始全1，没有0
            return;
        }
        int mid = (l + r) / 2;
        build(o * 2, l, mid);
        build(o * 2 + 1, mid + 1, r);
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
    }

    void apply(int o, int val) {
        if (val == 0) { // set to 0 (free)
            tree[o].sum = 0;
            tree[o].l0 = tree[o].len;
            tree[o].r0 = tree[o].len;
            tree[o].mx0 = tree[o].len;
            tree[o].lazy = 0;
        } else if (val == 1) { // set to 1 (occupied)
            tree[o].sum = tree[o].len;
            tree[o].l0 = 0;
            tree[o].r0 = 0;
            tree[o].mx0 = 0;
            tree[o].lazy = 1;
        }
    }

    void pushdown(int o) {
        if (tree[o].lazy != -1) {
            apply(o * 2, tree[o].lazy);
            apply(o * 2 + 1, tree[o].lazy);
            tree[o].lazy = -1;
        }
    }

    void update(int o, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l)
            return;
        if (ql <= l && r <= qr) {
            apply(o, val);
            return;
        }
        pushdown(o);
        int mid = (l + r) / 2;
        update(o * 2, l, mid, ql, qr, val);
        update(o * 2 + 1, mid + 1, r, ql, qr, val);
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
    }

    int querySum(int o, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;
        if (ql <= l && r <= qr) {
            return tree[o].sum;
        }
        pushdown(o);
        int mid = (l + r) / 2;
        return querySum(o * 2, l, mid, ql, qr) + querySum(o * 2 + 1, mid + 1, r, ql, qr);
    }

    Node queryNode(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[o];
        }
        pushdown(o);
        int mid = (l + r) / 2;
        if (qr <= mid)
            return queryNode(o * 2, l, mid, ql, qr);
        if (ql > mid)
            return queryNode(o * 2 + 1, mid + 1, r, ql, qr);
        Node left = queryNode(o * 2, l, mid, ql, qr);
        Node right = queryNode(o * 2 + 1, mid + 1, r, ql, qr);
        return merge(left, right);
    }

    int queryMax0(int o, int l, int r, int ql, int qr) {
        Node node = queryNode(o, l, r, ql, qr);
        return node.mx0;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Seg seg(n);
    seg.build(1, 1, n);

    while (m--) {
        int op;
        cin >> op;
        if (op == 0) {
            int l, r;
            cin >> l >> r;
            seg.update(1, 1, n, l, r, 0);
        } else if (op == 1) {
            int l0, r0, l1, r1;
            cin >> l0 >> r0 >> l1 >> r1;
            int cnt = seg.querySum(1, 1, n, l0, r0);
            seg.update(1, 1, n, l0, r0, 0);
            int ans = 0;
            if (cnt > 0) {
                int l = l1, r = r1 + 1;
                while (l < r) {
                    int m = (l + r) / 2;
                    int free = m - l1 + 1 - seg.querySum(1, 1, n, l1, m);
                    if (free <= cnt) {
                        l = m + 1;
                        ans = m;
                    } else {
                        r = m;
                    }
                }

                seg.update(1, 1, n, l1, ans, 1);
            }
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.queryMax0(1, 1, n, l, r) << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
