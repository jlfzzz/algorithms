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
struct SegmentTreeNode {
    ll val;
};

class SegmentTree {
private:
    int n;
    vector<SegmentTreeNode> tree;

    SegmentTreeNode merge(const SegmentTreeNode &left, const SegmentTreeNode &right) {
        return {min(left.val, right.val)};
    }

    void build(const vector<ll> &nums, int node, int l, int r) {
        if (l == r) {
            tree[node] = {nums[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(nums, node * 2, l, mid);
        build(nums, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, ll val) {
        if (l == r) {
            tree[node].val = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid)
            update(node * 2, l, mid, idx, val);
        else
            update(node * 2 + 1, mid + 1, r, idx, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return LLONG_MAX;
        if (ql <= l && r <= qr)
            return tree[node].val;
        int mid = (l + r) / 2;
        return min(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid + 1, r, ql, qr));
    }

public:
    explicit SegmentTree(const vector<ll> &nums) {
        n = nums.size();
        tree.resize(4 * n + 5);
        build(nums, 1, 0, n - 1);
    }

    explicit SegmentTree(int n) : n(n), tree(4 * n + 5) {}

    void update(int idx, ll val) { update(1, 0, n - 1, idx, val); }

    ll rangeMin(int l, int r) { return query(1, 0, n - 1, l, r); }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<int> L(n + 1, -1), R(n + 1, n + 1);
    vector<int> stk;

    for (int i = 1; i <= n; i++) {
        while (!stk.empty() && a[i] > a[stk.back()])
            stk.pop_back();
        L[i] = stk.empty() ? -1 : stk.back();
        stk.push_back(i);
    }

    stk.clear();
    for (int i = n; i >= 1; i--) {
        while (!stk.empty() && a[i] < a[stk.back()])
            stk.pop_back();
        R[i] = stk.empty() ? n + 1 : stk.back();
        stk.push_back(i);
    }

    vector<int> f(n + 1, n + 1);
    for (int i = 1; i <= n; i++) {
        if (L[i] != -1 && R[i] != n + 1) {
            f[L[i]] = min(f[L[i]], R[i] - 1);
        }
    }

    SegmentTree seg(n + 5);
    for (int i = 1; i <= n; i++) {
        seg.update(i, f[i]);
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        int x = seg.rangeMin(l, r);
        if (r <= x)
            cout << "YES\n";
        else
            cout << "NO\n";
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
