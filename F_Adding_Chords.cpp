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

struct Node {
    int val, lazy;
};

struct Seg {
    int n;
    vector<Node> tree;

    Seg(int n) : n(n), tree(4 * n + 5) {}

    void pushdown(int o, Node &l, Node &r) {
        if (tree[o].lazy) {
            l.lazy = r.lazy = tree[o].lazy;
            l.val = r.val = tree[o].val;
            tree[o].lazy = 0;
        }
    }

    void rangeChange(int o, int l, int r, int ql, int qr, int val) {
        if (l > qr || r < ql) {
            return;
        }

        if (l >= ql && r <= qr) {
            tree[o].lazy = val;
            tree[o].val = val;
            return;
        }

        int m = (l + r) / 2;
        pushdown(o, tree[o * 2], tree[o * 2 + 1]);
        rangeChange(o * 2, l, m, ql, qr, val);
        rangeChange(o * 2 + 1, m + 1, r, ql, qr, val);
    }

    int get(int o, int l, int r, int i) {
        if (l == r) {
            return tree[o].val;
        }

        int m = (l + r) / 2;
        pushdown(o, tree[o * 2], tree[o * 2 + 1]);
        if (i <= m) {
            return get(o * 2, l, m, i);
        }
        return get(o * 2 + 1, m + 1, r, i);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;

    Seg seg(n);
    int ts = 0;

    while (q--) {
        int a, b;
        cin >> a >> b;

        int v1 = seg.get(1, 1, n, a);
        int v2 = seg.get(1, 1, n, b);

        if (v1 != v2) {
            cout << "No\n";
        } else {
            cout << "Yes\n";
            ts += 1;
            int mn = min(a, b);
            int mx = max(a, b);

            if (mx - mn < n - (mx - mn)) {
                if (mn + 1 <= mx - 1) {
                    seg.rangeChange(1, 1, n, mn + 1, mx - 1, ts);
                }
            } else {
                if (mx + 1 <= n) {
                    seg.rangeChange(1, 1, n, mx + 1, n, ts);
                }
                if (1 <= mn - 1) {
                    seg.rangeChange(1, 1, n, 1, mn - 1, ts);
                }
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    //  >> T;
    while (T--)
        solve();
    return 0;
}
