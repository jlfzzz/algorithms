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

int Multitest = 1;

const long double PI_LD = acosl(-1.0L);

ll exgcd_pos(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = exgcd_pos(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

pii primitive(pii p) {
    ll x = p.fi, y = p.se;
    if (x == 0 && y == 0)
        return {0, 0};
    ll g = std::gcd(std::llabs(x), std::llabs(y));
    x /= g;
    y /= g;
    return {x, y};
}

void init() {}

void solve() {
    int n;
    rd(n);

    vp a(n);
    rv(a);

    vector<pair<long double, int>> ang_idx;
    ang_idx.reserve(n);
    F(i, 0, n - 1) {
        if (a[i].fi == 0 && a[i].se == 0)
            continue;
        long double ang = atan2((long double) a[i].se, (long double) a[i].fi);
        ang_idx.pb(ang, i);
    }

    int idx0 = ang_idx[0].se;
    ll bx = a[idx0].fi;
    ll by = a[idx0].se;

    bool onLine = true;
    bool pos = false, neg = false;

    for (auto &p: a) {
        ll x = p.fi, y = p.se;
        if (x == 0 && y == 0)
            continue;
        ll cross = bx * y - by * x;
        if (cross != 0)
            onLine = false;
        ll dot = bx * x + by * y;
        if (dot > 0)
            pos = true;
        else if (dot < 0)
            neg = true;
    }

    if (onLine && !neg) {
        pii u = primitive({bx, by});
        prt(1);
        prt(u.fi, u.se);
        return;
    }

    if (onLine) {
        pii posP{0, 0}, negP{0, 0};
        bool hasPos = false, hasNeg = false;
        for (auto &p: a) {
            ll x = p.fi, y = p.se;
            if (x == 0 && y == 0)
                continue;
            ll dot = bx * x + by * y;
            if (dot > 0 && !hasPos) {
                posP = p;
                hasPos = true;
            } else if (dot < 0 && !hasNeg) {
                negP = p;
                hasNeg = true;
            }
        }
        pii u = primitive(posP);
        pii v = primitive(negP);
        prt(2);
        prt(u.fi, u.se);
        prt(v.fi, v.se);
        return;
    }

    sort(all(ang_idx));
    int m = (int) ang_idx.size();
    vector<long double> ang(2 * m);
    for (int i = 0; i < m; i++) {
        ang[i] = ang_idx[i].fi;
        ang[i + m] = ang_idx[i].fi + 2 * PI_LD;
    }

    const long double EPS = 1e-12L;
    bool inHalf = false;
    int startId = -1;
    int j = 0;

    for (int i = 0; i < m; i++) {
        if (j < i)
            j = i;
        while (j < i + m && ang[j] - ang[i] < PI_LD - EPS) {
            j++;
        }
        if (j - i >= m) {
            inHalf = true;
            startId = i;
            break;
        }
    }

    if (inHalf) {
        int idx = ang_idx[startId % m].se;
        pii u = primitive(a[idx]);
        ll a1 = u.fi, b1 = u.se;

        ll aa = std::llabs(a1);
        ll bb = std::llabs(b1);

        if (aa == 0)
            aa = 1;
        ll s, t;
        exgcd_pos(aa, bb, s, t);

        ll signA = (a1 >= 0 ? 1 : -1);
        ll signB = (b1 >= 0 ? 1 : -1);

        ll d = s * signA;
        ll tprime = t * signB;
        ll c = -tprime;

        const ll K = 1000000000LL;
        ll c2 = c - K * a1;
        ll d2 = d - K * b1;

        prt(2);
        prt(a1, b1);
        prt(c2, d2);
        return;
    }

    prt(3);
    prt(0, 1);
    prt(1, 0);
    prt(-1, -1);
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
