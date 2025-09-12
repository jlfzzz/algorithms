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
    int mn, lazy;
};

class Seg {
public:
    int n;
    vector<Node> tree;

    Seg(int n, vector<int> &v) : n(n), tree(4 * n + 100) { build(1, 1, n, v); }

    Node merge(int o) {
        Node res{};
        res.mn = min(tree[o * 2].mn, tree[o * 2 + 1].mn);
        return res;
    }

    void build(int o, int l, int r, vector<int> &v) {
        if (l == r) {
            tree[o] = {v[l], 0};
            return;
        }

        int m = (l + r) / 2;
        build(o * 2, l, m, v);
        build(o * 2 + 1, m + 1, r, v);
        tree[o] = merge(o);
    }

    void pushdown(int o, int l, int r) {
        if (tree[o].lazy) {
            int v = tree[o].lazy;
            tree[o * 2].lazy += v;
            tree[o * 2].mn -= v;
            tree[o * 2 + 1].lazy += v;
            tree[o * 2 + 1].mn -= v;
            tree[o].lazy = 0;
        }
    }

    void rangeAdd(int o, int l, int r, int L, int R) {
        if (r < L || l > R) {
            return;
        }

        if (l >= L && r <= R) {
            tree[o].lazy += 1;
            tree[o].mn -= 1;
            return;
        }

        pushdown(o, l, r);
        int m = (l + r) / 2;
        rangeAdd(o * 2, l, m, L, R);
        rangeAdd(o * 2 + 1, m + 1, r, L, R);
        tree[o] = merge(o);
    }

    int rangeMin(int o, int l, int r, int L, int R) {
        if (r < L || l > R) {
            return inf;
        }

        if (l >= L && r <= R) {
            return tree[o].mn;
        }

        pushdown(o, l, r);
        int m = (l + r) / 2;
        return min(rangeMin(o * 2, l, m, L, R), rangeMin(o * 2 + 1, m + 1, r, L, R));
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> space(n + 1);
    For(i, n) cin >> space[i + 1];

    Seg seg(n, space);

    vector<pii> queries;
    while (m--) {
        int a, b;
        cin >> a >> b;
        queries.emplace_back(a, b);
    }

    ranges::sort(queries, [](pii &a, pii &b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });

    int ans = 0;
    for (auto &[l, r]: queries) {
        int mn = seg.rangeMin(1, 1, n, l, r);
        // cout << l << ' ' << r << endl;
        // cout << mn << endl;
        if (mn) {
            ans++;
            seg.rangeAdd(1, 1, n, l, r);
        }
    }

    cout << ans << '\n';
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
