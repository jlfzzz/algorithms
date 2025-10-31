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

int Multitest = 1;

void init() {}

struct Seg {
    vi tree;
    Seg(vi &v) : tree(4 * SZ(v) + 5) { build(1, 1, SZ(v) - 1, v); }

    void build(int o, int l, int r, vi &v) {
        if (l == r) {
            tree[o] = v[l];
            return;
        }

        int m = (l + r) / 2;
        build(o * 2, l, m, v);
        build(o * 2 + 1, m + 1, r, v);
        tree[o] = gcd(tree[o * 2], tree[o * 2 + 1]);
    }

    int query(int o, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) {
            return 0;
        }

        if (l >= ql && r <= qr) {
            return tree[o];
        }

        int m = (l + r) / 2;
        return gcd(query(o * 2, l, m, ql, qr), query(o * 2 + 1, m + 1, r, ql, qr));
    }
};

void solve() {
    int n;
    rd(n);
    vi a(n + 1);
    rv(a, 1);
    int g = 0;
    F(i, 1, n) { g = gcd(g, a[i]); }

    bool f = false;
    F(i, 1, n) {
        if (a[i] != g) {
            f = true;
        }
    }

    if (!f) {
        prt(0);
        return;
    }

    Seg seg(a);
    int lo = 1;
    int hi = n + 5;
    int ans = 0;

    while (lo < hi) {
        int m = (lo + hi) / 2;

        auto check = [&]() {
            F(i, 1, n) {
                int r = i + m - 1;
                int t;
                if (r <= n) {
                    t = seg.query(1, 1, n, i, r);
                } else {
                    t = gcd(seg.query(1, 1, n, i, n), seg.query(1, 1, n, 1, r - n));
                }
                if (t != g)
                    return false;
            }
            return true;
        };

        if (check()) {
            hi = m;
            ans = m;
        } else {
            lo = m + 1;
        }
    }

    prt(ans - 1);
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
