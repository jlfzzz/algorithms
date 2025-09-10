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
    ll mx, mn;
};

class SegmentTree {
private:
    int n;
    vector<SegmentTreeNode> tree;

    SegmentTreeNode merge(const SegmentTreeNode &left, const SegmentTreeNode &right) {
        return {max(left.mx, right.mx), min(left.mn, right.mn)};
    }

    void build(const vector<ll> &nums, int node, int l, int r) {
        if (l == r) {
            tree[node] = {nums[l], nums[l]};
            return;
        }
        int mid = (l + r) / 2;
        build(nums, node * 2, l, mid);
        build(nums, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, ll val) {
        if (l == r) {
            tree[node] = {val, val};
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
            return LLONG_MIN;
        if (ql <= l && r <= qr)
            return tree[node].mx;
        int mid = (l + r) / 2;
        return max(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid + 1, r, ql, qr));
    }

    ll query2(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return LLONG_MAX;
        if (ql <= l && r <= qr)
            return tree[node].mn;
        int mid = (l + r) / 2;
        return min(query2(node * 2, l, mid, ql, qr), query2(node * 2 + 1, mid + 1, r, ql, qr));
    }

public:
    // 1-index
    explicit SegmentTree(const vector<ll> &nums) {
        n = nums.size();
        tree.resize(4 * n + 5);
        build(nums, 1, 1, n);
    }

    explicit SegmentTree(int n) : n(n), tree(4 * n + 5) {}

    void update(int idx, ll val) { update(1, 1, n, idx, val); }

    ll rangeMax(int l, int r) { return query(1, 1, n, l, r); }

    ll rangeMin(int l, int r) { return query2(1, 1, n, l, r); }

    ll getValue(int idx) { return rangeMax(idx, idx); }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    For(i, n) cin >> a[i];
    For(i, n) cin >> b[i];

    SegmentTree segB(n + 1), segA(n + 1);
    for (int i = 1; i <= n; i++) {
        segB.update(i, b[i - 1]);
        segA.update(i, a[i - 1]);
    }

    vector<int> las(n + 2, -1);
    vector<bool> ok(n, 0);

    for (int i = 0; i < n; i++) {
        las[a[i]] = i;
        int p = las[b[i]];
        if (p == -1)
            continue;
        int mn = segB.rangeMin(p + 1, i + 1);
        int mx = segA.rangeMax(p + 1, i + 1);
        if (mn >= b[i] && mx <= b[i])
            ok[i] = 1;
    }

    fill(las.begin(), las.end(), -1);
    for (int i = n - 1; i >= 0; i--) {
        las[a[i]] = i;
        int p = las[b[i]];
        if (p == -1)
            continue;
        int mn = segB.rangeMin(i + 1, p + 1);
        int mx = segA.rangeMax(i + 1, p + 1);
        if (mn >= b[i] && mx <= b[i])
            ok[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (!ok[i]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
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
