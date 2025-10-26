#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define ld long double
#define db double
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

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

    struct range : ranges::view_base {
        struct Iterator {
            using iterator_category = random_access_iterator_tag;
            using value_type = long long;
            using difference_type = ptrdiff_t;
            ll val, d;
            Iterator() = default;
            Iterator(ll val, ll d) : val(val), d(d) {};
            value_type operator*() const { return val; }
            Iterator &operator++() { return val += d, *this; }
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            Iterator &operator--() { return val -= d, *this; }
            Iterator operator--(int) {
                Iterator tmp = *this;
                --(*this);
                return tmp;
            }
            difference_type operator-(const Iterator &other) const { return (val - other.val) / d; }
            bool operator==(const Iterator &other) const { return val == other.val; }
        };
        Iterator Begin, End;
        explicit range(ll n) : Begin(0, 1), End(max(n, ll{0}), 1) {};
        range(ll a, ll b, ll d = ll(1)) : Begin(a, d), End(b, d) {
            ll cnt = b == a or (b - a > 0) != (d > 0) ? 0 : (b - a) / d + bool((b - a) % d);
            End.val = a + max(cnt, ll(0)) * d;
        };
        [[nodiscard]] Iterator begin() const { return Begin; }
        [[nodiscard]] Iterator end() const { return End; };
        [[nodiscard]] ptrdiff_t size() const { return End - Begin; }
    };
} // namespace utils

using namespace utils;
#define int ll

struct MinNodeX {
    pair<ll, ll> v;
    MinNodeX(pair<ll, ll> vv = pair<ll, ll>(inf, -1)) : v(vv) {}
    static MinNodeX merge(const MinNodeX &a, const MinNodeX &b) { return MinNodeX(min(a.v, b.v)); }
    bool ok(ll x) const { return x <= v.first; }
};

struct MaxNodeX {
    pair<ll, ll> v;
    MaxNodeX(pair<ll, ll> vv = pair<ll, ll>(-inf, -1)) : v(vv) {}
    static MaxNodeX merge(const MaxNodeX &a, const MaxNodeX &b) { return MaxNodeX(max(a.v, b.v)); }
    bool ok(ll x) const { return v.first <= x; }
};

template<class N>
struct SegTreeX {
    vector<N> x;
    int s{};
    SegTreeX() = default;
    template<class T>
    explicit SegTreeX(const vector<T> &a) {
        int n = (int) a.size();
        s = 1;
        while (s < n)
            s <<= 1;
        x.assign(s * 2, N());
        for (int i = 0; i < n; i++)
            x[s + i] = N(a[i]);
        for (int i = s - 1; i >= 1; i--)
            x[i] = N::merge(x[i * 2], x[i * 2 + 1]);
    }

    N composite(int l, int r) {
        N lf, rt;
        l += s;
        r += s;
        while (l < r) {
            if (l & 1) {
                lf = N::merge(lf, x[l]);
                l++;
            }
            if (r & 1) {
                r--;
                rt = N::merge(x[r], rt);
            }
            l >>= 1;
            r >>= 1;
        }
        return N::merge(lf, rt);
    }
    template<class F, class... Args>
    pair<int, N> max_right(int l, F f, Args &&...args) {
        if (l >= s)
            return {s, N()};
        l += s;
        N sm;
        if (!(sm.*f)(forward<Args>(args)...))
            return {l - s, sm};
        do {
            while ((l & 1) == 0)
                l >>= 1;
            N tmp = N::merge(sm, x[l]);
            if ((tmp.*f)(forward<Args>(args)...)) {
                sm = tmp;
                l++;
            } else {
                while (l < s) {
                    l <<= 1;
                    tmp = N::merge(sm, x[l]);
                    if ((tmp.*f)(forward<Args>(args)...)) {
                        sm = tmp;
                        l++;
                    }
                }
                return {l - s, sm};
            }
        } while ((l & -l) != l);
        return {s, sm};
    }
};

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
        rd(a[i]);

    vector<pair<ll, ll>> rw(n);
    for (int i = 0; i < n; i++)
        rw[i] = {a[i], i};
    SegTreeX<MinNodeX> segMin(rw);
    SegTreeX<MaxNodeX> segMax(rw);

    int cur = 0, ans = 0;
    while (cur < n - 1) {
        int nx = -1;
        if (a[cur] < a[cur + 1]) {
            int lim = segMin.max_right(cur, &MinNodeX::ok, a[cur]).first;
            nx = segMax.composite(cur, lim).v.second;
        } else {
            int lim = segMax.max_right(cur, &MaxNodeX::ok, a[cur]).first;
            nx = segMin.composite(cur, lim).v.second;
        }
        cur = nx;
        ans++;
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
