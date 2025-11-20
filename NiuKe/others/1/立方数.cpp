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

namespace MillerRabin {
    ull qpow(ull a, ull d, ull mod) {
        ull r = 1;
        while (d) {
            if (d & 1) {
                r = (i128) r * a % mod;
            }
            a = (i128) a * a % mod;
            d >>= 1;
        }
        return r;
    }

    bool check(ull a, ull s, ull d, ull n) {
        if (n == a) {
            return true;
        }
        ull x = qpow(a, d, n);
        if (x == 1 || x == n - 1) {
            return true;
        }
        F(i, 1, (int) s - 1) {
            x = (i128) x * x % n;
            if (x == n - 1) {
                return true;
            }
        }
        return false;
    }

    bool is_prime(ull n) {
        if (n < 2) {
            return false;
        }
        static ull test_primes[] = {2ull, 3ull, 5ull, 7ull, 11ull, 13ull, 17ull, 19ull, 23ull, 29ull, 31ull, 37ull};
        for (ull p: test_primes) {
            if (n % p == 0) {
                return n == p;
            }
        }
        ull d = n - 1;
        ull s = 0;
        while ((d & 1) == 0) {
            d >>= 1;
            s++;
        }
        static ull bases[] = {2ull, 325ull, 9375ull, 28178ull, 450775ull, 9780504ull, 1795265022ull};
        for (ull a: bases) {
            if (a % n == 0) {
                continue;
            }
            if (!check(a, s, d, n)) {
                return false;
            }
        }
        return true;
    }
} // namespace MillerRabin

namespace PollardRho {
    mt19937_64 rng((uint64_t) chrono::steady_clock::now().time_since_epoch().count());

    ull mul_mod(ull a, ull b, ull mod) { return (ull) ((i128) a * b % mod); }

    ull f(ull x, ull c, ull mod) { return (mul_mod(x, x, mod) + c) % mod; }

    ull rho(ull n) {
        if ((n & 1ull) == 0ull) {
            return 2ull;
        }
        if (n % 3ull == 0ull) {
            return 3ull;
        }
        uniform_int_distribution<ull> dist(2ull, n - 2ull);
        ull c = dist(rng);
        ull x = dist(rng);
        ull y = x;
        ull d = 1;
        while (d == 1) {
            x = f(x, c, n);
            y = f(f(y, c, n), c, n);
            ull diff = x > y ? x - y : y - x;
            d = std::gcd(diff, n);
            if (d == n) {
                return rho(n);
            }
        }
        return d;
    }

    void factor(ull n, vector<ull> &res) {
        if (n == 1) {
            return;
        }
        if (MillerRabin::is_prime(n)) {
            res.pb(n);
            return;
        }
        ull d = rho(n);
        factor(d, res);
        factor(n / d, res);
    }
} // namespace PollardRho

vector<int> primes;

int Multitest = 1;

void init() {
    if (!primes.empty()) {
        return;
    }
    const int LIM = 100000;
    vector<bool> is_comp(LIM + 1);
    F(i, 2, LIM) {
        if (!is_comp[i]) {
            primes.pb(i);
        }
        for (int p: primes) {
            ll v = 1ll * i * p;
            if (v > LIM) {
                break;
            }
            is_comp[(int) v] = true;
            if (i % p == 0) {
                break;
            }
        }
    }
}

void solve() {
    ll n;
    rd(n);
    ll m = 1;

    ll t = n;
    for (int p: primes) {
        if (p > t) {
            break;
        }
        if (t % p != 0) {
            continue;
        }
        int cnt = 0;
        while (t % p == 0) {
            t /= p;
            cnt++;
            if (cnt % 3 == 0) {
                m *= p;
            }
        }
    }

    ll ans = 1;
    ll l = 1;
    ll r = 1000000;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        ll v = mid * mid * mid;
        if (v == t) {
            ans = mid;
            break;
        }
        if (v > t) {
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    m *= ans;
    prt(m);
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
