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

    // 点更新取 max
    void updateMax(int i, T val) {
        for (; i < (int) tree.size(); i += i & -i) {
            if (val > tree[i]) {
                tree[i] = val;
            }
        }
    }

    T preMax(int i) const {
        T res = numeric_limits<T>::min();
        for (; i > 0; i &= i - 1) {
            res = max(res, tree[i]);
        }
        return res;
    }
};

void solve() {
    int n, m, k;
    rd(n, m, k);

    vi X, Y;
    set<int> ver, hor;
    ver.insert(0);
    hor.insert(0);
    X.pb(0);
    Y.pb(0);
    X.pb(1e6 + 5);
    Y.pb(1e6 + 5);
    ver.insert(1e6 + 5);
    hor.insert(1e6 + 5);
    F(i, 1, n) {
        int t;
        rd(t);
        ver.insert(t);
        X.pb(t);
    }
    F(i, 1, m) {
        int t;
        rd(t);
        hor.insert(t);
        Y.pb(t);
    }

    vp pts(k);
    F(i, 0, k - 1) {
        int x, y;
        rd(x, y);
        pts[i] = {x, y};
        X.pb(x);
        Y.pb(y);
    }

    ranges::sort(X);
    ranges::sort(Y);
    X.erase(unique(all(X)), X.end());
    Y.erase(unique(all(Y)), Y.end());
    int szX = SZ(X);
    int szY = SZ(Y);

    auto idX = [&](int i) -> int { return ranges::lower_bound(X, i) - X.begin() + 1; };
    auto idY = [&](int i) -> int { return ranges::lower_bound(Y, i) - Y.begin() + 1; };

    ll ans = 0;
    {
        vvi items(szX + 1);
        FenwickTree<int> bit(szY + 1);
        for (auto [a, b]: pts) {
            if (hor.contains(b)) {
                continue;
            }
            int i = idX(a);
            items[i].pb(b);
        }

        F(i, 1, szX) {
            for (int y: items[i]) {
                int up = idY(*hor.upper_bound(y));
                int down = idY(*prev(hor.upper_bound(y)));
                ans += bit.rangeSum(down, up);
            }
            for (int y: items[i]) {
                int j = idY(y);
                bit.update(j, 1);
            }
        }
    }
    {
        vvi items(szY + 1);
        FenwickTree<int> bit(szX + 1);
        for (auto [a, b]: pts) {
            if (ver.contains(a)) {
                continue;
            }
            int i = idY(b);
            items[i].pb(a);
        }

        F(i, 1, szY) {
            for (int x: items[i]) {
                int up = idX(*ver.upper_bound(x));
                int down = idX(*prev(ver.upper_bound(x)));
                ans += bit.rangeSum(down, up);
            }
            for (int x: items[i]) {
                int j = idX(x);
                bit.update(j, 1);
            }
        }
    }

    prt(ans);
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
