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
    vector<ll> tree;
    Seg(int n, vl &arr) : tree(4 * (n + 1) + 5) { build(1, 1, n, arr); }

    void build(int o, int l, int r, vl &arr) {
        if (l == r) {
            tree[o] = arr[l];
            return;
        }

        int m = (l + r) / 2;
        build(o * 2, l, m, arr);
        build(o * 2 + 1, m + 1, r, arr);
        tree[o] = max(tree[o * 2], tree[o * 2 + 1]);
    }

    ll findFirst(int o, int l, int r, ll target) {
        if (l == r) {
            return l;
        }

        int m = (l + r) / 2;
        if (tree[o * 2] >= target) {
            return findFirst(o * 2, l, m, target);
        }
        return findFirst(o * 2 + 1, m + 1, r, target);
    }
};

void solve() {
    int n, m;
    rd(n, m);

    vl a(n + 1);
    rv(a, 1);

    ll sum = accumulate(a.begin() + 1, a.end(), 0ll);
    vl ans;
    vl pref(n + 1);
    F(i, 1, n) { pref[i] = pref[i - 1] + a[i]; }
    Seg seg(n, pref);
    ll mx = ranges::max(pref);
    if (sum <= 0) {
        while (m--) {
            ll target;
            rd(target);

            int i = seg.findFirst(1, 1, n, target);
            if (pref[i] < target) {
                ans.pb(-1);
            } else {
                ans.pb(i - 1);
            }
        }
    } else {
        while (m--) {
            ll target;
            rd(target);

            int i = seg.findFirst(1, 1, n, target);
            if (pref[i] < target) {
                ll need = (target - mx + sum - 1) / sum;
                target -= need * sum;
                need *= n;
                int j = seg.findFirst(1, 1, n, target);
                need += j - 1;
                ans.pb(need);
            } else {
                ans.pb(i - 1);
            }
        }
    }

    prv(ans);
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
