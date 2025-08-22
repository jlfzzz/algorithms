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

struct Node {
    int cost;
    int cnt;

    Node(int c = inf, int ct = 0) : cost(c), cnt(ct) {}

    Node operator+(const Node &other) const {
        if (cost < other.cost)
            return *this;
        if (cost > other.cost)
            return other;
        return Node(cost, (cnt + other.cnt) % MOD);
    }
};

struct LazySegTree {
    int n;
    vector<Node> tree;
    vector<Node> lazy;
    vector<bool> has_lazy;

    LazySegTree(int sz) : n(sz) {
        tree.resize(4 * n, Node());
        lazy.resize(4 * n, Node());
        has_lazy.resize(4 * n, false);
    }

    void push(int v, int tl, int tr) {
        if (has_lazy[v]) {
            // 应用懒惰更新 - 完全按照原始代码的逻辑
            Node &update = lazy[v];
            if (update.cost < tree[v].cost) {
                tree[v] = update;
            } else if (update.cost == tree[v].cost) {
                tree[v].cnt = (tree[v].cnt + update.cnt) % MOD;
            }
            // 如果 update.cost > tree[v].cost，则不更新（保持原值）

            if (tl != tr) {
                // 传播给子节点
                if (!has_lazy[2 * v]) {
                    lazy[2 * v] = update;
                    has_lazy[2 * v] = true;
                } else {
                    // 合并懒惰更新
                    if (update.cost < lazy[2 * v].cost) {
                        lazy[2 * v] = update;
                    } else if (update.cost == lazy[2 * v].cost) {
                        lazy[2 * v].cnt = (lazy[2 * v].cnt + update.cnt) % MOD;
                    }
                }

                if (!has_lazy[2 * v + 1]) {
                    lazy[2 * v + 1] = update;
                    has_lazy[2 * v + 1] = true;
                } else {
                    // 合并懒惰更新
                    if (update.cost < lazy[2 * v + 1].cost) {
                        lazy[2 * v + 1] = update;
                    } else if (update.cost == lazy[2 * v + 1].cost) {
                        lazy[2 * v + 1].cnt = (lazy[2 * v + 1].cnt + update.cnt) % MOD;
                    }
                }
            }

            has_lazy[v] = false;
            lazy[v] = Node();
        }
    }

    void update(int v, int tl, int tr, int l, int r, Node val) {
        push(v, tl, tr);
        if (l > r)
            return;
        if (l == tl && r == tr) {
            // 直接设置懒惰更新，push函数会处理合并逻辑
            lazy[v] = val;
            has_lazy[v] = true;
            push(v, tl, tr);
            return;
        }

        int tm = (tl + tr) / 2;
        update(2 * v, tl, tm, l, min(r, tm), val);
        update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
        push(2 * v, tl, tm);
        push(2 * v + 1, tm + 1, tr);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }

    Node query(int v, int tl, int tr, int pos) {
        push(v, tl, tr);
        if (tl == tr) {
            return tree[v];
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            return query(2 * v, tl, tm, pos);
        } else {
            return query(2 * v + 1, tm + 1, tr, pos);
        }
    }

    void update(int l, int r, Node val) { update(1, 0, n - 1, l, r, val); }

    Node query(int pos) { return query(1, 0, n - 1, pos); }
};

void init() {}

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];
    vector<int> b(m + 1);
    For(i, m) cin >> b[i + 1];

    if (ranges::max(a) > ranges::max(b)) {
        cout << -1 << '\n';
        return;
    }

    vector<LazySegTree> dp(m + 1, LazySegTree(n + 1));

    // 初始化
    dp[1].update(0, 0, Node(0, 1));

    vector<int> pre_sum(n + 1);
    for (int i = 1; i <= n; i++) {
        pre_sum[i] = pre_sum[i - 1] + a[i];
    }
    pre_sum.push_back(inf);

    for (int i = 1; i <= n; i++) {
        int pre_min = inf;
        int pre_cnt = 0;

        for (int j = 1; j <= m; j++) {
            int k = ranges::upper_bound(pre_sum, pre_sum[i - 1] + b[j]) - pre_sum.begin() - 1;
            if (k < i)
                break;

            Node prev = dp[j].query(i - 1);
            if (prev.cost == pre_min) {
                pre_cnt = (pre_cnt + prev.cnt) % MOD;
            } else if (prev.cost < pre_min) {
                pre_min = prev.cost;
                pre_cnt = prev.cnt % MOD;
            }

            // 用线段树进行区间更新，替代原来的 for (int l = i; l <= k; l++)
            if (pre_min != inf) {
                dp[j].update(i, k, Node(pre_min + m - j, pre_cnt));
            }
        }
    }

    int ans = inf;
    int ans_cnt = 0;

    for (int j = 1; j <= m; j++) {
        Node result = dp[j].query(n);
        if (result.cost != inf && ans == result.cost) {
            ans_cnt = (ans_cnt + result.cnt) % MOD;
        } else if (result.cost != inf && result.cost < ans) {
            ans = result.cost;
            ans_cnt = result.cnt % MOD;
        }
    }

    if (ans == inf) {
        cout << -1 << '\n';
    } else {
        cout << ans << ' ' << (ans_cnt % MOD) << '\n';
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
