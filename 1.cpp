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

int Multitest = 0;

void init() {}

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick() : n(0) {}
    explicit Fenwick(int n_) { init(n_); }
    void init(int n_) {
        n = n_;
        bit.assign(n + 1, 0);
    }
    void add(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += delta;
    }
    int sumPrefix(int idx) const {
        int s = 0;
        for (; idx > 0; idx -= idx & -idx)
            s += bit[idx];
        return s;
    }
};

struct SegTree {
    struct Node {
        ll x, y;
        bool flip;
    };
    int n;
    vector<Node> st;
    SegTree() : n(0) {}
    explicit SegTree(int n_) { init(n_); }
    void init(int n_) {
        n = max(1, n_); // 保证有一棵树（题面 T>=2）
        st.assign(4 * n + 5, {0, 0, false});
    }
    static void applyFlip(Node &nd) {
        nd.x = -nd.x;
        nd.y = -nd.y;
        nd.flip = !nd.flip;
    }
    void push(int p) {
        if (!st[p].flip)
            return;
        applyFlip(st[p << 1]);
        applyFlip(st[p << 1 | 1]);
        st[p].flip = false;
    }
    static Node merge(const Node &a, const Node &b) { return {a.x + b.x, a.y + b.y, false}; }
    void pointSet(int p, int l, int r, int idx, ll vx, ll vy) {
        if (l == r) {
            st[p].x = vx;
            st[p].y = vy;
            st[p].flip = false;
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        if (idx <= m)
            pointSet(p << 1, l, m, idx, vx, vy);
        else
            pointSet(p << 1 | 1, m + 1, r, idx, vx, vy);
        st[p] = merge(st[p << 1], st[p << 1 | 1]);
    }
    void rangeNeg(int p, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return;
        if (ql <= l && r <= qr) {
            applyFlip(st[p]);
            return;
        }
        push(p);
        int m = (l + r) >> 1;
        rangeNeg(p << 1, l, m, ql, qr);
        rangeNeg(p << 1 | 1, m + 1, r, ql, qr);
        st[p] = merge(st[p << 1], st[p << 1 | 1]);
    }
    void setPoint(int idx, ll vx, ll vy) { pointSet(1, 1, n, idx, vx, vy); }
    void negateRange(int l, int r) {
        if (l <= r)
            rangeNeg(1, 1, n, l, r);
    }
    pair<ll, ll> queryAll() const { return {st[1].x, st[1].y}; }
};

static inline pair<ll, ll> relVecByT(long long t) {
    int m = int(t & 3LL);
    if (m == 0)
        return {-1, 0};
    if (m == 1)
        return {0, 1};
    if (m == 2)
        return {1, 0};
    return {0, -1};
}

void solve() {
    int Nq;
    int Tlen;
    if (!(cin >> Nq >> Tlen))
        return;
    // 线段树覆盖 [1 .. T-1] 的时间点；每个叶子存当前带符号贡献 (+/- d_b)，初始为 0
    SegTree st(max(1, Tlen - 1));
    Fenwick fw(Tlen - 1); // 只用到 1..T-1

    auto d0 = relVecByT(0);
    auto dT = relVecByT(Tlen);
    long long k = 0; // 已插入个数

    for (int i = 0; i < Nq; i++) {
        int b;
        cin >> b; // 1 <= b <= T-1
        int cntLess = (b > 1 ? fw.sumPrefix(b - 1) : 0);
        int sign = (cntLess % 2 == 0 ? +1 : -1);
        auto vecB = relVecByT(b);
        ll vx = sign * vecB.first, vy = sign * vecB.second;
        st.setPoint(b, vx, vy);
        if (b < Tlen - 1)
            st.negateRange(b + 1, Tlen - 1);
        fw.add(b, 1);
        k++;

        auto S = st.queryAll();
        long long addTx = (k % 2 == 0 ? dT.first : 0);
        long long addTy = (k % 2 == 0 ? dT.second : 0);
        long long ansx = S.first + addTx - d0.first;
        long long ansy = S.second + addTy - d0.second;
        cout << ansx << ' ' << ansy << '\n';
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
