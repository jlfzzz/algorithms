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

int mod;
struct SegmentTreeNode {
    ll val, lazy1, lazy2;
};

class SegmentTree {
private:
    SegmentTreeNode merge(const SegmentTreeNode &left, const SegmentTreeNode &right) {
        SegmentTreeNode res;
        res.val = (left.val + right.val) % mod;
        res.lazy1 = 0;
        res.lazy2 = 1;
        return res;
    }

    void apply(int node, int l, int r) {
        if (tree[node].lazy1) {
            tree[node].val += (r - l + 1) * tree[node].lazy1 % mod;
        } else if (tree[node].lazy2) {
            tree[node].val = tree[node].val * tree[node].lazy2 % mod;
        }
    }

    void pushDown(int node, int l, int r) {
        if (tree[node].lazy1 || tree[node].lazy2) {
            int mid = (l + r) / 2;
            apply(node * 2, l, mid);
            apply(node * 2 + 1, mid + 1, r);
            tree[node].lazy1 = tree[node].lazy2 = 0;
        }
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
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void rangeAdd(int node, int l, int r, int ql, int qr, ll val) {
        if (qr < l || r < ql)
            return;
        if (ql <= l && r <= qr) {
            tree[node].lazy1 += val;
            apply(node, l, r);
            return;
        }
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        rangeAdd(node * 2, l, mid, ql, qr, val);
        rangeAdd(node * 2 + 1, mid + 1, r, ql, qr, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void rangeMul(int node, int l, int r, int ql, int qr, ll val) {
        if (qr < l || r < ql)
            return;
        if (ql <= l && r <= qr) {
            tree[node].lazy2 += val;
            apply(node, l, r);
            return;
        }
        pushDown(node, l, r);
        int mid = (l + r) / 2;
        rangeMul(node * 2, l, mid, ql, qr, val);
        rangeMul(node * 2 + 1, mid + 1, r, ql, qr, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
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
    int n;
    vector<SegmentTreeNode> tree;
    explicit SegmentTree(const vector<ll> &nums) {
        n = nums.size();
        tree.resize(4 * n + 5);
        build(nums, 1, 0, n - 1);
    }

    explicit SegmentTree(int n) : n(n), tree(4 * n + 5) {}

    void build(const vector<ll> &nums, int node, int l, int r) {
        if (l == r) {
            tree[node] = {nums[l], 0};
            return;
        }
        int mid = (l + r) / 2;
        build(nums, node * 2, l, mid);
        build(nums, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int idx, ll val) { update(1, 0, n - 1, idx, val); }

    void rangeAdd(int l, int r, ll val) { rangeAdd(1, 0, n - 1, l, r, val); }

    void rangeMul(int l, int r, ll val) { rangeMul(1, 0, n - 1, l, r, val); }

    ll rangeSum(int l, int r) { return query(1, 0, n - 1, l, r); }

    ll getValue(int idx) { return rangeSum(idx, idx); }
};

void solve() {
    int n, q, m;
    cin >> n >> q >> m;
    vector<int> a(n + 1);
    mod = m;
    For(i, n) cin >> a[i + 1];

    SegmentTree st(a);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, y, k;
            cin >> x >> y >> k;

            st.rangeMul(x, y, k);
        } else if (op == 2) {
            int x, y, k;
            cin >> x >> y >> k;

            st.rangeAdd(x, y, k);
        } else {
            int x, y;
            cin >> x >> y;

            cout << st.rangeSum(x, y) << '\n';
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
