#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
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

constexpr int N = 1e5 + 5;

int Multitest = 0;

void init() {}

struct BIT {
    vector<int> tree;
    int n;
    BIT(int n) : tree(n + 1), n(n) {}

    void add(int i, int val) {
        for (; i <= n; i += i & -i) {
            tree[i] += val;
        }
    }

    int pre(int i) {
        int res = 0;
        while (i) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
};

void solve2() {
    int n;
    rd(n);

    vi a(n + 1);
    rv(a, 1);

    ll ans = 0;
    vvi lazy(n + 10);
    BIT bit(n + 10);

    F(i, 1, n) {
        for (int idx: lazy[i]) {
            bit.add(idx, -1);
        }

        int cur = a[i];
        int t = bit.pre(min(cur, i - 1));
        dbg(i, t);
        ans += t;
        if (cur > i) {
            bit.add(i, 1);
            if (cur + 1 <= n) {
                lazy[cur + 1].pb(i);
            }
        }
    }

    prt(ans);
}

int ts = 0;
int tree[40 * N], ls[40 * N], rs[40 * N];

int upd(int pre, int l, int r, int i, int val) {
    int cur = ++ts;
    ls[cur] = ls[pre];
    rs[cur] = rs[pre];
    tree[cur] = tree[pre] + val;
    if (l == r) {
        return cur;
    }

    int m = (l + r) / 2;
    if (i <= m) {
        ls[cur] = upd(ls[pre], l, m, i, val);
    } else {
        rs[cur] = upd(rs[pre], m + 1, r, i, val);
    }

    return cur;
}

int query(int pre, int cur, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) {
        return 0;
    }

    if (l >= ql && r <= qr) {
        return tree[cur] - tree[pre];
    }

    int m = (l + r) / 2;
    return query(ls[pre], ls[cur], l, m, ql, qr) + query(rs[pre], rs[cur], m + 1, r, ql, qr);
}

void solve() {
    int n;
    rd(n);

    vi a(n + 1);
    rv(a, 1);

    F(i, 1, n) {
        if (a[i] > n)
            a[i] = n;
    }

    ts = 0;
    vi root(n + 5);
    root[0] = 0;

    F(i, 1, n) { root[i] = upd(root[i - 1], 1, n, a[i], 1); }

    ll ans = 0;

    F(i, 1, n) {
        int R = min(a[i], i - 1);
        ans += query(0, root[R], 1, n, i, n);
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
