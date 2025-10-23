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

struct Seg {
    int n;
    vector<int> tree;

    Seg(int n) : n(n), tree(4 * n + 5) { build(1, 1, n); }

    void pushup(int o) { tree[o] = tree[o * 2] + tree[o * 2 + 1]; }

    void build(int o, int l, int r) {
        if (l == r) {
            tree[o] = 1;
            return;
        }

        int m = (l + r) / 2;
        build(o * 2, l, m);
        build(o * 2 + 1, m + 1, r);
        pushup(o);
    }

    void update(int o, int l, int r, int i) {
        if (l == r) {
            tree[o] = 0;
            return;
        }

        int m = (l + r) / 2;
        if (i <= m) {
            update(o * 2, l, m, i);
        } else {
            update(o * 2 + 1, m + 1, r, i);
        }
        pushup(o);
    }

    int query(int o, int l, int r, int L, int R) {
        if (r < L || l > R) {
            return 0;
        }

        if (l >= L && r <= R) {
            return tree[o];
        }

        int m = (l + r) / 2;
        return query(o * 2, l, m, L, R) + query(o * 2 + 1, m + 1, r, L, R);
    }
};

void solve2() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    Seg seg(n);
    int m;
    cin >> m;

    // struct Query {
    //     int l, r, id;
    // };

    // vector<Query> queries(n + 1);
    // For(i, m) {
    //     int l, r;
    //     cin >> l >> r;
    //     queries[i] = {l, r, i};
    // }

    // sort(queries.begin() + 1, queries.end(), [](Query & a, Query & b))

    vector<vector<pii>> ev(n + 1);
    For(i, m) {
        int l, r;
        cin >> l >> r;
        ev[r].emplace_back(l, i + 1);
    }

    int mx_a = ranges::max(a);
    vector<int> ans(m + 1);
    vector<int> last(mx_a + 1);
    for (int i = 1; i <= n; i++) {
        int x = a[i];
        if (last[x]) {
            seg.update(1, 1, n, last[x]);
        }
        last[x] = i;

        if (!ev[i].empty()) {

            for (auto &[l, id]: ev[i]) {
                // cout << "l is: " << l << " r is: " << i << " id is: " << id << '\n';
                ans[id] = seg.query(1, 1, n, l, i);
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        cout << ans[i] << '\n';
    }
}

template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}

    void update(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 左闭右闭
    T rangeSum(int l, int r) const { return this->pre(r) - this->pre(l - 1); }

    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    T getVal(int i) { return rangeSum(i, i); }

    void setVal(int i, T val) {
        T delta = val - getVal(i);
        update(i, delta);
    }

    // 点更新取 max
    void updateMax(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            if (val > tree[i]) {
                tree[i] = val;
            }
        }
    }

    T preMax(int i) const {
        T res = numeric_limits<T>::min();
        for (; i > 0; i &= i - 1) {
            res = max(res, tree[i]);
        }
        return res;
    }
};


#define int ll

int Multitest = 0;

void init() {}

void solve() {
    int n;
    rd(n);
    vector<int> a(n + 1);
    rd_vec(a, 1);
    int q;
    rd(q);

    vector<vector<pii>> queries(n + 1);
    vector<int> ans(q + 1);

    for (int i: range(q)) {
        int l, r;
        rd(l, r);

        queries[r].eb(l, i + 1);
    }

    FenwickTree<int> fwt(n + 1);
    map<int, int> last;
    for (int i: range(1, n + 1)) {
        int cur = a[i];
        if (last[cur]) {
            fwt.update(last[cur], -1);
        }
        last[cur] = i;
        fwt.update(i, 1);

        for (auto [l, id]: queries[i]) {
            int have = fwt.rangeSum(l, i);
            ans[id] = have;
        }
    }

    for (int i: range(1, q + 1)) {
        prt(ans[i]);
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
