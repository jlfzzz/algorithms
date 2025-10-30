#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

namespace utils {
    void dbg() { cerr << "\n"; }

    template<typename T, typename... Args>
    void dbg(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        dbg(args...);
    }

    template<typename T>
    void prt(const T &x) {
        cout << x << '\n';
    }

    template<typename T, typename... Args>
    void prt(const T &first, const Args &...rest) {
        cout << first;
        ((cout << ' ' << rest), ...);
        cout << '\n';
    }

    template<typename T>
    void prv(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prv(const vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void rd(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void rd(T &x, Args &...args) {
        cin >> x;
        rd(args...);
    }

    template<typename A, typename B>
    void rd(pair<A, B> &p) {
        cin >> p.first >> p.second;
    }

    template<typename T>
    void rv(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rv(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace utils

using namespace utils;

constexpr int N = 1e6 + 5;

struct Node {
    int val = 0;
};

class PST {
private:
    int n, ts;
    std::vector<int> lc, rc;
    std::vector<Node> tree;

    void newnode(int pre, int cur) {
        lc[cur] = lc[pre];
        rc[cur] = rc[pre];
        tree[cur] = tree[pre];
    }

    Node merge(const Node &left, const Node &right) { return Node{left.val + right.val}; }

    int _build(const std::vector<int> &arr, int l, int r) {
        int cur = ++ts;
        if (l == r) {
            tree[cur] = Node{arr[l]};
            return cur;
        }
        int m = (l + r) / 2;
        lc[cur] = _build(arr, l, m);
        rc[cur] = _build(arr, m + 1, r);
        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    int _update(int pre, int l, int r, int pos, int val) {
        int cur = ++ts;
        newnode(pre, cur);
        if (l == r) {
            tree[cur].val += val;
            return cur;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            lc[cur] = _update(lc[pre], l, m, pos, val);
        else
            rc[cur] = _update(rc[pre], m + 1, r, pos, val);

        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    int _query(int cur, int pre, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return 0;
        if (ql <= l && r <= qr)
            return tree[cur].val - tree[pre].val;
        int m = (l + r) / 2;
        return _query(lc[cur], lc[pre], l, m, ql, qr) + _query(rc[cur], rc[pre], m + 1, r, ql, qr);
    }

    int _kth(int cur, int pre, int l, int r, int k) {
        if (l == r)
            return l;
        int cnt = tree[lc[cur]].val - tree[lc[pre]].val;
        int m = (l + r) / 2;
        if (k <= cnt)
            return _kth(lc[cur], lc[pre], l, m, k);
        else
            return _kth(rc[cur], rc[pre], m + 1, r, k - cnt);
    }

public:
    std::vector<int> root;

    PST(int n, int updates_hint) : n(n), ts(0) {
        int max_nodes = 22 * (n + max(1, updates_hint)) + 5;
        lc.assign(max_nodes, 0);
        rc.assign(max_nodes, 0);
        tree.assign(max_nodes, Node{});
        root.assign(max_nodes, 0);
    }

    PST(int n) : PST(n, n) {}

    int build(const std::vector<int> &arr) { return _build(arr, 1, n); }

    int update(int pre_version, int pos, int val) { return _update(pre_version, 1, n, pos, val); }

    int query(int cur_version, int pre_version, int l, int r) { return _query(cur_version, pre_version, 1, n, l, r); }

    int kth(int cur_version, int pre_version, int k) { return _kth(cur_version, pre_version, 1, n, k); }
};

int Multitest = 1;

void init() {}

void solve() {
    int n, q;
    rd(n, q);
    vl a(n + 1);
    rv(a, 1);

    vl comp = a;
    sort(all(comp));
    comp.erase(unique(all(comp)), comp.end());
    int m = (int) comp.size();
    auto getIdx = [&](int x) { return int(lower_bound(all(comp), x) - comp.begin()) + 1; };

    vl ar(n + 1);
    for (int i = 1; i <= n; ++i)
        ar[i] = getIdx(a[i]);

    PST pst(m, n);
    vl zeros(m + 1, 0);
    int base = pst.build(vector<int>(all(zeros)));
    vl roots(n + 1, 0);
    roots[0] = base;
    for (int i = 1; i <= n; ++i) {
        roots[i] = pst.update(roots[i - 1], ar[i], 1);
    }

    auto cnt_one = [&](int l, int r, int rk) { return pst.query(roots[r], roots[l - 1], rk, rk); };

    auto kth_rank = [&](int l, int r, int k) { return pst.kth(roots[r], roots[l - 1], k); };

    while (q--) {
        int l, r;
        rd(l, r);
        int len = r - l + 1;
        int thr = len / 3;
        int k1 = len / 3 + 1;
        int k2 = (2 * len) / 3 + 1;

        vl candidates;
        int rk1 = kth_rank(l, r, k1);
        int rk2 = kth_rank(l, r, k2);
        candidates.pb(rk1);
        if (rk2 != rk1)
            candidates.pb(rk2);

        vl ans;
        for (int rk: candidates) {
            int c = cnt_one(l, r, rk);
            if (c > thr)
                ans.pb(comp[rk - 1]);
        }
        sort(all(ans));
        ans.erase(unique(all(ans)), ans.end());

        if (ans.empty()) {
            prt(-1);
        } else {
            prv(ans);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--) {
        solve();
    }
}
