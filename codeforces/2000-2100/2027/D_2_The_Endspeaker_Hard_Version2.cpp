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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

struct Node {
    int cost;
    int cnt;
    int lazy_cost;
    int lazy_cnt;

    Node() : cost(inf), cnt(0), lazy_cost(inf), lazy_cnt(0) {}

    void combine(const Node &other) {
        if (other.cost < cost) {
            cost = other.cost;
            cnt = other.cnt % MOD;
        } else if (other.cost == cost) {
            cnt = (cnt + other.cnt) % MOD;
        }
    }
};

class Seg {
public:
    vector<Node> tree;
    int n_;

    explicit Seg(int n) : tree(4 * n), n_(n) {}

    void push(int o, int l, int r) {
        if (tree[o].lazy_cost != inf) {
            if (tree[o].lazy_cost < tree[o].cost) {
                tree[o].cost = tree[o].lazy_cost;
                tree[o].cnt = tree[o].lazy_cnt % MOD;
            } else if (tree[o].lazy_cost == tree[o].cost) {
                tree[o].cnt = (tree[o].cnt + tree[o].lazy_cnt) % MOD;
            }

            if (l != r) {
                for (int child: {o * 2, o * 2 + 1}) {
                    if (tree[o].lazy_cost < tree[child].lazy_cost) {
                        tree[child].lazy_cost = tree[o].lazy_cost;
                        tree[child].lazy_cnt = tree[o].lazy_cnt % MOD;
                    } else if (tree[o].lazy_cost == tree[child].lazy_cost) {
                        tree[child].lazy_cnt = (tree[child].lazy_cnt + tree[o].lazy_cnt) % MOD;
                    }
                }
            }

            tree[o].lazy_cost = inf;
            tree[o].lazy_cnt = 0;
        }
    }

    void update(int o, int l, int r, int L, int R, int cost, int cnt) {
        push(o, l, r);
        if (l > R || r < L)
            return;

        if (L <= l && r <= R) {
            if (cost < tree[o].lazy_cost) {
                tree[o].lazy_cost = cost;
                tree[o].lazy_cnt = cnt % MOD;
            } else if (cost == tree[o].lazy_cost) {
                tree[o].lazy_cnt = (tree[o].lazy_cnt + cnt) % MOD;
            }
            push(o, l, r);
            return;
        }

        int mid = (l + r) / 2;
        update(o * 2, l, mid, L, R, cost, cnt);
        update(o * 2 + 1, mid + 1, r, L, R, cost, cnt);

        tree[o] = tree[o * 2];
        tree[o].combine(tree[o * 2 + 1]);
    }

    Node query(int o, int l, int r, int pos) {
        push(o, l, r);
        if (l == r)
            return tree[o];

        int mid = (l + r) / 2;
        if (pos <= mid)
            return query(o * 2, l, mid, pos);
        else
            return query(o * 2 + 1, mid + 1, r, pos);
    }

    void update(int l, int r, int cost, int cnt) { update(1, 0, n_ - 1, l, r, cost, cnt); }

    Node query(int pos) { return query(1, 0, n_ - 1, pos); }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    For(i, n) cin >> a[i];
    vector<int> b(m);
    For(i, m) cin >> b[i];

    if (ranges::max(a) > ranges::max(b)) {
        cout << -1 << '\n';
        return;
    }

    vector<int> pre(n + 1);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i - 1];
    }

    vector<Seg> segs(m + 1, Seg(n + 1));

    segs[1].update(0, 0, 0, 1);

    for (int i = 1; i <= n; i++) {
        Node best_prev;
        best_prev.cost = inf;
        best_prev.cnt = 0;

        for (int j = 1; j <= m; j++) {
            Node prev_state = segs[j].query(i - 1);
            if (prev_state.cost != inf) {
                if (prev_state.cost < best_prev.cost) {
                    best_prev = prev_state;
                } else if (prev_state.cost == best_prev.cost) {
                    best_prev.cnt = (best_prev.cnt + prev_state.cnt) % MOD;
                }
            }

            if (best_prev.cost == inf)
                continue;

            int y = b[j - 1];
            int curr_pre = pre[i - 1];

            int nxt_i = upper_bound(pre.begin(), pre.end(), curr_pre + y) - pre.begin() - 1;
            if (nxt_i < i)
                continue;

            int new_cost = best_prev.cost + (m - j);
            segs[j].update(i, nxt_i, new_cost, best_prev.cnt);
        }
    }

    int ans_cost = inf;
    int ans_cnt = 0;
    for (int j = 1; j <= m; j++) {
        Node result = segs[j].query(n);
        if (result.cost < ans_cost) {
            ans_cost = result.cost;
            ans_cnt = result.cnt % MOD;
        } else if (result.cost == ans_cost) {
            ans_cnt = (ans_cnt + result.cnt) % MOD;
        }
    }

    if (ans_cost == inf) {
        cout << -1 << '\n';
    } else {
        cout << ans_cost << ' ' << ans_cnt << '\n';
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
