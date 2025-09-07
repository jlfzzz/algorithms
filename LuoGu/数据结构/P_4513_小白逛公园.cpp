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
    int sum, pre, suf, best;
};

class Seg {
private:
    void update(int o, int l, int r, int i, int val) {
        if (l == r) {
            tree[o] = {val, val, val, val};
            return;
        }
        int m = (l + r) / 2;
        if (i <= m)
            update(o * 2, l, m, i, val);
        else
            update(o * 2 + 1, m + 1, r, i, val);
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
    }

    Node query(int o, int l, int r, int L, int R) {
        if (L > r || R < l) {
            return {0, -inf, -inf, -inf};
        }
        if (l >= L && r <= R) {
            return tree[o];
        }
        int m = (l + r) / 2;
        Node left = query(o * 2, l, m, L, R);
        Node right = query(o * 2 + 1, m + 1, r, L, R);
        return merge(left, right);
    }

    void build(vector<int> &arr, int o, int l, int r) {
        if (l == r) {
            int val = arr[l];
            tree[o] = {val, val, val, val};
            return;
        }
        int m = (l + r) / 2;
        build(arr, o * 2, l, m);
        build(arr, o * 2 + 1, m + 1, r);
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
    }

public:
    int n;
    vector<Node> tree;

    Seg(int n) : n(n), tree(4 * n + 5) {}

    Node merge(const Node &left, const Node &right) {
        Node res;
        res.sum = left.sum + right.sum;
        res.pre = max(left.pre, left.sum + right.pre);
        res.suf = max(right.suf, right.sum + left.suf);
        res.best = max({left.best, right.best, left.suf + right.pre});
        return res;
    }

    void build(vector<int> &arr) { build(arr, 1, 1, n); }

    void update(int i, int val) { update(1, 1, n, i, val); }

    Node query(int L, int R) { return query(1, 1, n, L, R); }

    int queryBest(int L, int R) { return query(L, R).best; }
};


void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> vals(n + 1);
    For(i, n) cin >> vals[i + 1];

    Seg seg(n);
    seg.build(vals);
    while (m--) {
        int k;
        cin >> k;

        if (k == 1) {
            int a, b;
            cin >> a >> b;

            if (b < a) {
                swap(a, b);
            }

            cout << seg.query(a, b).best << '\n';
        } else {
            int p, s;
            cin >> p >> s;

            seg.update(p, s);
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
