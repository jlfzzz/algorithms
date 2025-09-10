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
    int val, del;
};

class Seg {
public:
    int n;
    vector<ll> tree, tag;

    Seg(int n) : n(n), tree(4 * n + 10), tag(4 * n + 10, 0) {}

    void push_up(int o) { tree[o] = max(tree[o * 2], tree[o * 2 + 1]); }

    void push_down(int o) {
        if (tag[o] == 0)
            return;
        tree[o * 2] += tag[o];
        tag[o * 2] += tag[o];
        tree[o * 2 + 1] += tag[o];
        tag[o * 2 + 1] += tag[o];
        tag[o] = 0;
    }

    void update(int o, int l, int r, int ql, int qr, int val) {
        if (ql <= l && r <= qr) {
            tree[o] += val;
            tag[o] += val;
            return;
        }
        push_down(o);
        int m = (l + r) / 2;
        if (ql <= m)
            update(o * 2, l, m, ql, qr, val);
        if (qr > m)
            update(o * 2 + 1, m + 1, r, ql, qr, val);
        push_up(o);
    }

    int query(int o, int l, int r, int ql, int qr) {
        if (ql > qr)
            return 0;
        if (ql <= l && r <= qr) {
            return tree[o];
        }
        push_down(o);
        int m = (l + r) / 2;
        int max_val = 0;
        if (ql <= m)
            max_val = max(max_val, query(o * 2, l, m, ql, qr));
        if (qr > m)
            max_val = max(max_val, query(o * 2 + 1, m + 1, r, ql, qr));
        return max_val;
    }
};

struct Request {
    int s, e, m;
    bool operator<(const Request &other) const { return e < other.e; }
};

void solve() {
    int k, n, c;
    cin >> k >> n >> c;
    vector<Request> reqs(k);
    For(i, k) { cin >> reqs[i].s >> reqs[i].e >> reqs[i].m; }

    sort(reqs.begin(), reqs.end());

    Seg seg(n + 1);
    ll ans = 0;

    for (const auto &req: reqs) {
        int s = req.s;
        int e = req.e;
        int m = req.m;

        int current_max_load = seg.query(1, 1, n, s, e - 1);

        int can_take = min(m, (int) (c - current_max_load));

        if (can_take > 0) {
            ans += can_take;
            seg.update(1, 1, n, s, e - 1, can_take);
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
