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
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n;
    long long k;
    rd(n, k);
    vl a(n + 1), b(n + 1), c(n + 1);
    F(i, 1, n) {
        rd(a[i]);
    }
    F(i, 1, n) {
        rd(b[i]);
    }
    F(i, 1, n) {
        rd(c[i]);
    }
    long long maxB = 0;
    F(i, 1, n) {
        if (b[i] > maxB) {
            maxB = b[i];
        }
    }
    auto need_pair = [&](int i, long long y) -> long long {
        long long s0 = a[i] + a[i + 1];
        long long D = y - s0;
        if (D <= 0) {
            return 0;
        }
        long long v1 = b[i], m1 = c[i];
        long long v2 = b[i + 1], m2 = c[i + 1];
        if (v1 < v2) {
            swap(v1, v2);
            swap(m1, m2);
        }
        __int128 Smax = (__int128) v1 * m1 + (__int128) v2 * m2;
        if ((__int128) D > Smax) {
            return (long long) 4e18;
        }
        auto ceil_div = [](__int128 A, __int128 B) -> long long {
            if (A <= 0) {
                return 0LL;
            }
            return (long long) ((A + B - 1) / B);
        };
        __int128 cap1 = (__int128) v1 * m1;
        if ((__int128) D <= cap1) {
            return ceil_div(D, v1);
        } else {
            __int128 rem = (__int128) D - cap1;
            return (long long) m1 + ceil_div(rem, v2);
        }
    };
    auto ok = [&](long long y) -> bool {
        vector<long long> w(n + 1, (long long) 4e18);
        F(i, 1, n - 1) {
            w[i] = need_pair(i, y);
        }
        const long long INFLL = (long long) 4e18;
        vector<long long> dp1(n + 1, INFLL), dp2(n + 1, INFLL), dp3(n + 1, INFLL);
        dp1[0] = INFLL;
        dp2[0] = INFLL;
        dp3[0] = INFLL;
        F(i, 1, n - 1) {
            dp1[i] = dp1[i - 1];
            if (w[i] < dp1[i]) {
                dp1[i] = w[i];
            }
            dp2[i] = dp2[i - 1];
            if (i >= 2) {
                if (dp1[i - 2] < INFLL && w[i] < INFLL) {
                    long long cand = dp1[i - 2] + w[i];
                    if (cand < dp2[i]) {
                        dp2[i] = cand;
                    }
                }
            }
            dp3[i] = dp3[i - 1];
            if (i >= 2) {
                if (dp2[i - 2] < INFLL && w[i] < INFLL) {
                    long long cand = dp2[i - 2] + w[i];
                    if (cand < dp3[i]) {
                        dp3[i] = cand;
                    }
                }
            }
        }
        if (dp3[n - 1] <= k) {
            return true;
        } else {
            return false;
        }
    };
    long long baseMax = 0;
    F(i, 1, n - 1) {
        long long s0 = a[i] + a[i + 1];
        if (s0 > baseMax) {
            baseMax = s0;
        }
    }
    long long lo = 0, hi = baseMax + (__int128) k * maxB;
    while (lo < hi) {
        long long mid = lo + ((hi - lo + 1) >> 1);
        if (ok(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    long long y = lo;
    long long p = y;
    long long q = 2;
    long long g = gcd(p, q);
    p /= g;
    q /= g;
    cout << p << '/' << q << '\n';
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
