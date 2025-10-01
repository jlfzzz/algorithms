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

namespace io {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
    }

    template<typename... Args>
    void prt(const Args &...args) {
        ((cout << args << " "), ...);
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename End, typename... Args>
    void prt_end(const End &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename... Args>
    void prt_endl(const Args &...args) {
        ((cout << args << " "), ...);
        cout << endl;
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
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace io

using namespace io;

int Multitest = 1;

template<typename T>
class FenwickTree {
    vector<T> tree;

public:
    FenwickTree(int n) : tree(n + 1) {}

    void update(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            tree[i] += val;
        }
    }

    // 左闭右闭
    T rangeSum(int l, int r) const { return this->pre(r) - this->pre(l - 1); }

    T pre(int i) const {
        T res = 0;
        for (; i > 0; i &= i - 1) {
            res += tree[i];
        }
        return res;
    }

    T getVal(int i) { return rangeSum(i, i); }

    void setVal(int i, T val) {
        T delta = val - getVal(i);
        update(i, delta);
    }
};

void init() {}

void solve() {
    int n;
    rd(n);

    vector<int> a(n + 1);
    rd_vec(a, 1);

    FenwickTree<int> pre(n + 1);

    int ans = 0;

    pre.update(a[1], 1);
    for (int i = 2; i + 2 <= n; i++) {
        FenwickTree<int> suf(n + 1);
        for (int j = n; j >= i + 1; j--) {
            suf.update(a[j], 1);
        }
        for (int j = i + 1; j + 1 <= n; j++) {
            suf.update(a[j], -1);

            int b = a[i];
            int c = a[j];

            int a = pre.pre(c - 1);
            int d = suf.pre(b - 1);
            ans += a * d;
        }

        pre.update(a[i], 1);
    }

    prt(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--)
        solve();
    return 0;
}
