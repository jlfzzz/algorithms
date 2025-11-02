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

struct Seg {
    struct Node {
        int mx = 0;
        ll cnt = 0;
        ll ors = 0;
        ll ands = 0;
        ll lazyAdd = 0;
        ll lazyRemove = 0;
    };
    vector<Node> tree;
    int n;

    Seg(int _n) : n(_n) {
        tree.resize(4 * n + 4);
        build(1, 1, n);
    }

    int popcount(ll x) { return __builtin_popcountll(x); }

    void pushup(int p) {
        Node &L = tree[p * 2];
        Node &R = tree[p * 2 + 1];
        tree[p].mx = max(L.mx, R.mx);
        tree[p].cnt = 0;
        if (tree[p].mx == L.mx)
            tree[p].cnt += L.cnt;
        if (tree[p].mx == R.mx)
            tree[p].cnt += R.cnt;
        tree[p].ors = L.ors | R.ors;
        tree[p].ands = L.ands & R.ands;
    }

    void apply(int p, ll add, ll rem) {
        tree[p].ors = (tree[p].ors | add) & ~rem;
        tree[p].ands = (tree[p].ands | add) & ~rem;
        tree[p].lazyAdd = (tree[p].lazyAdd | add) & ~rem;
        tree[p].lazyRemove = (tree[p].lazyRemove | rem) & ~add;
    }

    void push(int p) {
        if (tree[p].lazyAdd == 0 && tree[p].lazyRemove == 0)
            return;

        ll add = tree[p].lazyAdd;
        ll rem = tree[p].lazyRemove;
        ll bits = add | rem;

        Node &L = tree[p * 2];
        if (((L.ors & bits) == (L.ands & bits))) {
            int old = popcount(L.ands & bits);
            int nxt = popcount((L.ands | add) & ~rem & bits);
            L.mx += (nxt - old);
        }
        apply(p * 2, add, rem);

        Node &R = tree[p * 2 + 1];
        if (((R.ors & bits) == (R.ands & bits))) {
            int old = popcount(R.ands & bits);
            int nxt = popcount((R.ands | add) & ~rem & bits);
            R.mx += (nxt - old);
        }
        apply(p * 2 + 1, add, rem);

        tree[p].lazyAdd = 0;
        tree[p].lazyRemove = 0;
    }

    void build(int p, int l, int r) {
        if (l == r) {
            tree[p].mx = 0;
            tree[p].cnt = 1;
            tree[p].ors = 0;
            tree[p].ands = 0;
            return;
        }
        int m = (l + r) / 2;
        build(p * 2, l, m);
        build(p * 2 + 1, m + 1, r);
        pushup(p);
    }

    void update(int p, int l, int r, int ql, int qr, ll add, ll rem) {
        if (qr < l || r < ql)
            return;

        ll bits = add | rem;

        if (((tree[p].ands & add) == add) && ((tree[p].ors & rem) == 0)) {
            return;
        }

        if (ql <= l && r <= qr && ((tree[p].ors & bits) == (tree[p].ands & bits))) {
            int old = popcount(tree[p].ands & bits);
            int nxt = popcount((tree[p].ands | add) & ~rem & bits);
            tree[p].mx += (nxt - old);
            apply(p, add, rem);
            return;
        }

        push(p);
        int m = (l + r) / 2;
        update(p * 2, l, m, ql, qr, add, rem);
        update(p * 2 + 1, m + 1, r, ql, qr, add, rem);
        pushup(p);
    }

    pii query(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql)
            return {-1, 0};

        if (ql <= l && r <= qr) {
            return {tree[p].mx, tree[p].cnt};
        }

        push(p);
        int m = (l + r) / 2;
        pii resL = query(p * 2, l, m, ql, qr);
        pii resR = query(p * 2 + 1, m + 1, r, ql, qr);

        if (resL.fi > resR.fi)
            return resL;
        if (resR.fi > resL.fi)
            return resR;
        return {resL.fi, resL.se + resR.se};
    }
};

int Multitest = 0;

void init() {}

void solve() {
    int n, q;
    rd(n, q);

    Seg seg(n);

    F(i, 1, q) {
        int op;
        rd(op);
        if (op == 1) {
            int L, R, x;
            rd(L, R, x);
            ll bit = (1ll << (x - 1));
            seg.update(1, 1, n, L, R, bit, 0);
        } else if (op == 2) {
            int L, R, x;
            rd(L, R, x);
            ll bit = (1ll << (x - 1));
            seg.update(1, 1, n, L, R, 0, bit);
        } else {
            int L, R;
            rd(L, R);
            pii res = seg.query(1, 1, n, L, R);
            prt(res.fi, res.se);
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
