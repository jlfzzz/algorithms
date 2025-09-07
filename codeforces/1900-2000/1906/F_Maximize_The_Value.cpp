#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)

void init() {}

struct Node {
    int sum, pre, suf, best;
};

static const long long NEG = -(1LL << 60);

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
            return {0, (int) NEG, (int) NEG, (int) NEG};
        }
        if (l >= L && r <= R) {
            return tree[o];
        }
        int m = (l + r) / 2;
        Node left = query(o * 2, l, m, L, R);
        Node right = query(o * 2 + 1, m + 1, r, L, R);
        return merge(left, right);
    }

    void add(int o, int l, int r, int i, int delta) {
        if (l == r) {
            tree[o].sum += delta;
            int val = tree[o].sum;
            tree[o] = {val, val, val, val};
            return;
        }
        int m = (l + r) / 2;
        if (i <= m)
            add(o * 2, l, m, i, delta);
        else
            add(o * 2 + 1, m + 1, r, i, delta);
        tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
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

    explicit Seg(int n) : n(n), tree(4 * n + 5) {}

    Seg(int n, vector<int> &arr) : n(n), tree(4 * n + 5) { build(arr); }

    static Node merge(const Node &left, const Node &right) {
        Node res{};
        res.sum = left.sum + right.sum;
        res.pre = max(left.pre, left.sum + right.pre);
        res.suf = max(right.suf, right.sum + left.suf);
        res.best = max({left.best, right.best, left.suf + right.pre});
        return res;
    }

    void build(vector<int> &arr) { build(arr, 1, 1, n); }

    void update(int i, int val) { update(1, 1, n, i, val); }

    void add(int i, int delta) { add(1, 1, n, i, delta); }

    Node query(int L, int R) { return query(1, 1, n, L, R); }

    int queryBest(int L, int R) { return query(L, R).best; }
};


void solve() {
    int n, m;
    cin >> n >> m;
    struct Op {
        int L, R, X;
    };
    vector<Op> op(m + 1);
    for (int i = 1; i <= m; ++i) {
        int L, R, X;
        cin >> L >> R >> X;
        op[i] = {L, R, X};
    }

    int q;
    cin >> q;
    struct Qry {
        int S, T, id;
    };
    vector<vector<Qry>> qs(n + 2);
    for (int i = 0; i < q; ++i) {
        int K, S, T;
        cin >> K >> S >> T;
        qs[K].push_back({S, T, i});
    }

    vector<vector<pair<int, int>>> ev(n + 3);
    for (int i = 1; i <= m; ++i) {
        ev[op[i].L].push_back({i, op[i].X});
        if (op[i].R + 1 <= n)
            ev[op[i].R + 1].push_back({i, -op[i].X});
    }

    Seg seg(m);
    vector<int> ans(q, 0);
    for (int k = 1; k <= n; ++k) {
        for (auto &e: ev[k])
            seg.add(e.first, e.second);
        if (!qs[k].empty()) {
            for (auto &qq: qs[k]) {
                ans[qq.id] = seg.queryBest(qq.S, qq.T);
            }
        }
    }

    for (int i = 0; i < q; ++i)
        cout << ans[i] << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    solve();
    return 0;
}
