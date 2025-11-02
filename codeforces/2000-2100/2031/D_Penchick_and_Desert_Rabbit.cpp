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
    vector<int> tree;
    Seg(int n) : tree(4 * n + 5, 0) {}

    void upd(int o, int l, int r, int i, int val) {
        if (l == r) {
            tree[o] = max(val, tree[o]);
            return;
        }

        int m = (l + r) / 2;
        if (i <= m) {
            upd(o * 2, l, m, i, val);
        } else {
            upd(o * 2 + 1, m + 1, r, i, val);
        }
        tree[o] = max(tree[o * 2], tree[o * 2 + 1]);
    }

    int query(int o, int l, int r, int ql, int qr) {
        if (l > qr || r < ql) {
            return 0;
        }

        if (l >= ql && r <= qr) {
            return tree[o];
        }

        int m = (l + r) / 2;
        return max(query(o * 2, l, m, ql, qr), query(o * 2 + 1, m + 1, r, ql, qr));
    }
};

void solve() {
    int n;
    rd(n);

    vi a(n + 1);
    rv(a, 1);

    vi preMx(n + 1);
    F(i, 1, n) { preMx[i] = max(a[i], preMx[i - 1]); }

    Seg seg(n);
    vi dp(n + 1, 0);
    D(i, n, 1) {
        int pre = preMx[i];
        int best = 0;
        if (pre > 1)
            best = seg.query(1, 1, n, 1, pre - 1);
        dp[i] = max(pre, best);
        seg.upd(1, 1, n, a[i], dp[i]);
    }

    prv(dp, 1);
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
