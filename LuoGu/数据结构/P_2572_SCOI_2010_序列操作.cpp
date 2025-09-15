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
    int sum, left, right, len, lazy, mx;
    int sum0, left0, right0, mx0;
};

struct Seg {
    int n;
    vector<Node> tree;

    Seg(int n, string &s) : n(n), tree(4 * n) { build(1, 1, n, s); }

    Node merge(const Node &L, const Node &R) {
        Node res{};
        res.len = L.len + R.len;
        res.lazy = 0;

        res.sum = L.sum + R.sum;
        res.left = (L.left == L.len) ? (L.len + R.left) : L.left;
        res.right = (R.right == R.len) ? (R.len + L.right) : R.right;
        res.mx = max({L.mx, R.mx, L.right + R.left});

        res.sum0 = L.sum0 + R.sum0;
        res.left0 = (L.left0 == L.len) ? (L.len + R.left0) : L.left0;
        res.right0 = (R.right0 == R.len) ? (R.len + L.right0) : R.right0;
        res.mx0 = max({L.mx0, R.mx0, L.right0 + R.left0});

        return res;
    }

    Node merge(int o) { return merge(tree[o * 2], tree[o * 2 + 1]); }

    void build(int o, int l, int r, string &s) {
        if (l == r) {
            int val = s[l] - '0';
            if (val) {
                tree[o] = {1, 1, 1, 1, 0, 1, 0, 0, 0, 0};
            } else {
                tree[o] = {0, 0, 0, 1, 0, 0, 1, 1, 1, 1};
            }
            return;
        }

        int m = (l + r) / 2;
        build(o * 2, l, m, s);
        build(o * 2 + 1, m + 1, r, s);
        tree[o] = merge(o);
    }

    void apply(int o, int tag) {
        if (tag == 1) {
            int len = tree[o].len;
            tree[o].sum = 0;
            tree[o].left = 0;
            tree[o].right = 0;
            tree[o].mx = 0;
            tree[o].sum0 = len;
            tree[o].left0 = len;
            tree[o].right0 = len;
            tree[o].mx0 = len;
            tree[o].lazy = 1;
        } else if (tag == 2) {
            int len = tree[o].len;
            tree[o].sum = len;
            tree[o].left = len;
            tree[o].right = len;
            tree[o].mx = len;
            tree[o].sum0 = 0;
            tree[o].left0 = 0;
            tree[o].right0 = 0;
            tree[o].mx0 = 0;
            tree[o].lazy = 2;
        } else if (tag == 3) {
            swap(tree[o].sum, tree[o].sum0);
            swap(tree[o].left, tree[o].left0);
            swap(tree[o].right, tree[o].right0);
            swap(tree[o].mx, tree[o].mx0);
            if (tree[o].lazy == 0)
                tree[o].lazy = 3;
            else if (tree[o].lazy == 1)
                tree[o].lazy = 2;
            else if (tree[o].lazy == 2)
                tree[o].lazy = 1;
            else if (tree[o].lazy == 3)
                tree[o].lazy = 0;
        }
    }

    void pushdown(int o) {
        if (!tree[o].lazy)
            return;
        int t = tree[o].lazy;
        apply(o * 2, t);
        apply(o * 2 + 1, t);
        tree[o].lazy = 0;
    }

    void update(int o, int l, int r, int L, int R, int op) {
        if (r < L || l > R) {
            return;
        }

        if (l >= L && r <= R) {
            apply(o, op);
            return;
        }

        int m = (l + r) / 2;
        pushdown(o);
        update(o * 2, l, m, L, R, op);
        update(o * 2 + 1, m + 1, r, L, R, op);
        tree[o] = merge(o);
    }

    Node query(int o, int l, int r, int L, int R) {
        if (r < L || l > R) {
            return Node{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        }
        if (L <= l && r <= R)
            return tree[o];
        pushdown(o);
        int m = (l + r) / 2;
        if (R <= m)
            return query(o * 2, l, m, L, R);
        if (L > m)
            return query(o * 2 + 1, m + 1, r, L, R);
        Node a = query(o * 2, l, m, L, R);
        Node b = query(o * 2 + 1, m + 1, r, L, R);
        return merge(a, b);
    }
};

void init() {}

void solve() {
    int n, m;
    if (!(cin >> n >> m))
        return;
    string s(n + 1, '0');
    for (int i = 1; i <= n; i += 1) {
        int x;
        cin >> x;
        s[i] = char('0' + x);
    }
    Seg seg(n, s);
    for (int i = 0; i < m; i += 1) {
        int op, l, r;
        cin >> op >> l >> r;
        int L = l + 1, R = r + 1;
        if (op == 0)
            seg.update(1, 1, n, L, R, 1);
        else if (op == 1)
            seg.update(1, 1, n, L, R, 2);
        else if (op == 2)
            seg.update(1, 1, n, L, R, 3);
        else if (op == 3) {
            auto res = seg.query(1, 1, n, L, R);
            cout << res.sum << '\n';
        } else if (op == 4) {
            auto res = seg.query(1, 1, n, L, R);
            cout << res.mx << '\n';
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
