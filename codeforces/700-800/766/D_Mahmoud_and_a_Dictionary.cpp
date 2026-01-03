#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define us unsigned
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD2 = int(1e9 + 7);
constexpr int MOD = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

namespace utils {
    template<typename A, typename B>
    ostream &operator<<(ostream &os, const pair<A, B> &p) {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template<typename Tuple, size_t... Is>
    void print_tuple(ostream &os, const Tuple &t, index_sequence<Is...>) {
        ((os << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
    }

    template<typename... Args>
    ostream &operator<<(ostream &os, const tuple<Args...> &t) {
        os << '(';
        print_tuple(os, t, index_sequence_for<Args...>{});
        return os << ')';
    }

    template<typename T, typename = decltype(begin(declval<T>())), typename = enable_if_t<!is_same_v<T, string>>>
    ostream &operator<<(ostream &os, const T &v) {
        os << '{';
        bool first = true;
        for (auto &x: v) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << '}';
    }

    void debug_out() { cerr << endl; }

    template<typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cerr << H;
        if (sizeof...(T))
            cerr << " ";
        debug_out(T...);
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

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

struct DSU {
    vi p;
    vi bad;

    DSU(int n) {
        p.resize(n + 1);
        iota(all(p), 0);
        bad.assign(n + 1, 0);
    }

    int find(int x) {
        if (p[x] == x)
            return x;
        return p[x] = find(p[x]);
    }

    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry)
            p[rx] = ry;
    }

    void unite1(int u, int v) {
        int ru = find(u);
        int badu = bad[ru];

        int rv = find(v);
        int badv = bad[rv];

        if (badu == rv || badv == ru) {
            prt("NO");
            return;
        }

        prt("YES");

        unite(ru, rv);

        if (badu != 0 && badv != 0) {
            unite(badu, badv);
        }

        int nroot = find(ru);
        int nbad = 0;
        if (badu != 0)
            nbad = find(badu);
        else if (badv != 0)
            nbad = find(badv);

        bad[nroot] = nbad;
        if (nbad != 0)
            bad[nbad] = nroot;
    }

    void unite2(int u, int v) {
        int ru = find(u);
        int badu = bad[ru];

        int rv = find(v);
        int badv = bad[rv];

        if (ru == rv) {
            prt("NO");
            return;
        }

        prt("YES");

        if (badv != 0) {
            unite(ru, badv);
        }

        if (badu != 0) {
            unite(rv, badu);
        }

        int ruu = find(u);
        int rvv = find(v);

        bad[ruu] = rvv;
        bad[rvv] = ruu;
    }

    int query(int u, int v) {
        int ru = find(u);
        int rv = find(v);

        if (ru == rv)
            return 1;
        if (bad[ru] == rv)
            return 2;
        return 3;
    }
};

void solve() {
    int n, m, q;
    rd(n, m, q);

    vector<string> s(n);
    map<string, int> mp;

    F(i, 0, n - 1) {
        rd(s[i]);
        mp[s[i]] = i + 1;
    }

    DSU dsu(n);

    F(i, 1, m) {
        int t;
        string w1, w2;
        rd(t, w1, w2);
        int u = mp[w1];
        int v = mp[w2];

        if (t == 1) {
            dsu.unite1(u, v);
        } else {
            dsu.unite2(u, v);
        }
    }

    F(i, 1, q) {
        string w1, w2;
        rd(w1, w2);
        int u = mp[w1];
        int v = mp[w2];
        prt(dsu.query(u, v));
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
