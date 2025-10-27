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

namespace atcoder {

    namespace internal {

#ifndef _MSC_VER
        template<class T>
        using is_signed_int128 =
            typename std::conditional<std::is_same<T, __int128_t>::value || std::is_same<T, __int128>::value,
                                      std::true_type, std::false_type>::type;

        template<class T>
        using is_unsigned_int128 =
            typename std::conditional<std::is_same<T, __uint128_t>::value || std::is_same<T, unsigned __int128>::value,
                                      std::true_type, std::false_type>::type;

        template<class T>
        using make_unsigned_int128 =
            typename std::conditional<std::is_same<T, __int128_t>::value, __uint128_t, unsigned __int128>;

        template<class T>
        using is_integral = typename std::conditional<std::is_integral<T>::value || is_signed_int128<T>::value ||
                                                          is_unsigned_int128<T>::value,
                                                      std::true_type, std::false_type>::type;

        template<class T>
        using is_signed_int =
            typename std::conditional<(is_integral<T>::value && std::is_signed<T>::value) || is_signed_int128<T>::value,
                                      std::true_type, std::false_type>::type;

        template<class T>
        using is_unsigned_int = typename std::conditional<(is_integral<T>::value && std::is_unsigned<T>::value) ||
                                                              is_unsigned_int128<T>::value,
                                                          std::true_type, std::false_type>::type;

        template<class T>
        using to_unsigned =
            typename std::conditional<is_signed_int128<T>::value, make_unsigned_int128<T>,
                                      typename std::conditional<std::is_signed<T>::value, std::make_unsigned<T>,
                                                                std::common_type<T>>::type>::type;

#else

        template<class T>
        using is_integral = typename std::is_integral<T>;

        template<class T>
        using is_signed_int = typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                                                        std::true_type, std::false_type>::type;

        template<class T>
        using is_unsigned_int = typename std::conditional<is_integral<T>::value && std::is_unsigned<T>::value,
                                                          std::true_type, std::false_type>::type;

        template<class T>
        using to_unsigned =
            typename std::conditional<is_signed_int<T>::value, std::make_unsigned<T>, std::common_type<T>>::type;

#endif

        template<class T>
        using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

        template<class T>
        using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

        template<class T>
        using to_unsigned_t = typename to_unsigned<T>::type;

    } // namespace internal

    namespace internal {

        // @param m `1 <= m`
        // @return x mod m
        constexpr long long safe_mod(long long x, long long m) {
            x %= m;
            if (x < 0)
                x += m;
            return x;
        }

        // Fast modular multiplication by barrett reduction
        // Reference: https://en.wikipedia.org/wiki/Barrett_reduction
        // NOTE: reconsider after Ice Lake
        struct barrett {
            unsigned int _m;
            unsigned long long im;

            // @param m `1 <= m`
            explicit barrett(unsigned int m) : _m(m), im((unsigned long long) (-1) / m + 1) {}

            // @return m
            unsigned int umod() const { return _m; }

            // @param a `0 <= a < m`
            // @param b `0 <= b < m`
            // @return `a * b % m`
            unsigned int mul(unsigned int a, unsigned int b) const {
                // [1] m = 1
                // a = b = im = 0, so okay

                // [2] m >= 2
                // im = ceil(2^64 / m)
                // -> im * m = 2^64 + r (0 <= r < m)
                // let z = a*b = c*m + d (0 <= c, d < m)
                // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
                // c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2
                // ((ab * im) >> 64) == c or c + 1
                unsigned long long z = a;
                z *= b;
#ifdef _MSC_VER
                unsigned long long x;
                _umul128(z, im, &x);
#else
                unsigned long long x = (unsigned long long) (((unsigned __int128) (z) *im) >> 64);
#endif
                unsigned long long y = x * _m;
                return (unsigned int) (z - y + (z < y ? _m : 0));
            }
        };

        // @param n `0 <= n`
        // @param m `1 <= m`
        // @return `(x ** n) % m`
        constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
            if (m == 1)
                return 0;
            unsigned int _m = (unsigned int) (m);
            unsigned long long r = 1;
            unsigned long long y = safe_mod(x, m);
            while (n) {
                if (n & 1)
                    r = (r * y) % _m;
                y = (y * y) % _m;
                n >>= 1;
            }
            return r;
        }

        // Reference:
        // M. Forisek and J. Jancina,
        // Fast Primality Testing for Integers That Fit into a Machine Word
        // @param n `0 <= n`
        constexpr bool is_prime_constexpr(int n) {
            if (n <= 1)
                return false;
            if (n == 2 || n == 7 || n == 61)
                return true;
            if (n % 2 == 0)
                return false;
            long long d = n - 1;
            while (d % 2 == 0)
                d /= 2;
            constexpr long long bases[3] = {2, 7, 61};
            for (long long a: bases) {
                long long t = d;
                long long y = pow_mod_constexpr(a, t, n);
                while (t != n - 1 && y != 1 && y != n - 1) {
                    y = y * y % n;
                    t <<= 1;
                }
                if (y != n - 1 && t % 2 == 0) {
                    return false;
                }
            }
            return true;
        }
        template<int n>
        constexpr bool is_prime = is_prime_constexpr(n);

        // @param b `1 <= b`
        // @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
        constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
            a = safe_mod(a, b);
            if (a == 0)
                return {b, 0};

            // Contracts:
            // [1] s - m0 * a = 0 (mod b)
            // [2] t - m1 * a = 0 (mod b)
            // [3] s * |m1| + t * |m0| <= b
            long long s = b, t = a;
            long long m0 = 0, m1 = 1;

            while (t) {
                long long u = s / t;
                s -= t * u;
                m0 -= m1 * u; // |m1 * u| <= |m1| * s <= b

                // [3]:
                // (s - t * u) * |m1| + t * |m0 - m1 * u|
                // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
                // = s * |m1| + t * |m0| <= b

                auto tmp = s;
                s = t;
                t = tmp;
                tmp = m0;
                m0 = m1;
                m1 = tmp;
            }
            // by [3]: |m0| <= b/g
            // by g != b: |m0| < b/g
            if (m0 < 0)
                m0 += b / s;
            return {s, m0};
        }

        // Compile time primitive root
        // @param m must be prime
        // @return primitive root (and minimum in now)
        constexpr int primitive_root_constexpr(int m) {
            if (m == 2)
                return 1;
            if (m == 167772161)
                return 3;
            if (m == 469762049)
                return 3;
            if (m == 754974721)
                return 11;
            if (m == 998244353)
                return 3;
            int divs[20] = {};
            divs[0] = 2;
            int cnt = 1;
            int x = (m - 1) / 2;
            while (x % 2 == 0)
                x /= 2;
            for (int i = 3; (long long) (i) *i <= x; i += 2) {
                if (x % i == 0) {
                    divs[cnt++] = i;
                    while (x % i == 0) {
                        x /= i;
                    }
                }
            }
            if (x > 1) {
                divs[cnt++] = x;
            }
            for (int g = 2;; g++) {
                bool ok = true;
                for (int i = 0; i < cnt; i++) {
                    if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                        ok = false;
                        break;
                    }
                }
                if (ok)
                    return g;
            }
        }
        template<int m>
        constexpr int primitive_root = primitive_root_constexpr(m);

        // @param n `n < 2^32`
        // @param m `1 <= m < 2^32`
        // @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)
        unsigned long long floor_sum_unsigned(unsigned long long n, unsigned long long m, unsigned long long a,
                                              unsigned long long b) {
            unsigned long long ans = 0;
            while (true) {
                if (a >= m) {
                    ans += n * (n - 1) / 2 * (a / m);
                    a %= m;
                }
                if (b >= m) {
                    ans += n * (b / m);
                    b %= m;
                }

                unsigned long long y_max = a * n + b;
                if (y_max < m)
                    break;
                // y_max < m * (n + 1)
                // floor(y_max / m) <= n
                n = (unsigned long long) (y_max / m);
                b = (unsigned long long) (y_max % m);
                std::swap(m, a);
            }
            return ans;
        }

    } // namespace internal

    namespace internal {

        struct modint_base {};
        struct static_modint_base : modint_base {};

        template<class T>
        using is_modint = std::is_base_of<modint_base, T>;
        template<class T>
        using is_modint_t = std::enable_if_t<is_modint<T>::value>;

    } // namespace internal

    template<int m, std::enable_if_t<(1 <= m)> * = nullptr>
    struct static_modint : internal::static_modint_base {
        using mint = static_modint;

    public:
        static constexpr int mod() { return m; }
        static mint raw(int v) {
            mint x;
            x._v = v;
            return x;
        }

        static_modint() : _v(0) {}
        template<class T, internal::is_signed_int_t<T> * = nullptr>
        static_modint(T v) {
            long long x = (long long) (v % (long long) (umod()));
            if (x < 0)
                x += umod();
            _v = (unsigned int) (x);
        }
        template<class T, internal::is_unsigned_int_t<T> * = nullptr>
        static_modint(T v) {
            _v = (unsigned int) (v % umod());
        }

        int val() const { return _v; }

        mint &operator++() {
            _v++;
            if (_v == umod())
                _v = 0;
            return *this;
        }
        mint &operator--() {
            if (_v == 0)
                _v = umod();
            _v--;
            return *this;
        }
        mint operator++(int) {
            mint result = *this;
            ++*this;
            return result;
        }
        mint operator--(int) {
            mint result = *this;
            --*this;
            return result;
        }

        mint &operator+=(const mint &rhs) {
            _v += rhs._v;
            if (_v >= umod())
                _v -= umod();
            return *this;
        }
        mint &operator-=(const mint &rhs) {
            _v -= rhs._v;
            if (_v >= umod())
                _v += umod();
            return *this;
        }
        mint &operator*=(const mint &rhs) {
            unsigned long long z = _v;
            z *= rhs._v;
            _v = (unsigned int) (z % umod());
            return *this;
        }
        mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }

        mint operator+() const { return *this; }
        mint operator-() const { return mint() - *this; }

        mint pow(long long n) const {
            assert(0 <= n);
            mint x = *this, r = 1;
            while (n) {
                if (n & 1)
                    r *= x;
                x *= x;
                n >>= 1;
            }
            return r;
        }
        mint inv() const {
            if (prime) {
                assert(_v);
                return pow(umod() - 2);
            } else {
                auto eg = internal::inv_gcd(_v, m);
                assert(eg.first == 1);
                return eg.second;
            }
        }

        friend mint operator+(const mint &lhs, const mint &rhs) { return mint(lhs) += rhs; }
        friend mint operator-(const mint &lhs, const mint &rhs) { return mint(lhs) -= rhs; }
        friend mint operator*(const mint &lhs, const mint &rhs) { return mint(lhs) *= rhs; }
        friend mint operator/(const mint &lhs, const mint &rhs) { return mint(lhs) /= rhs; }
        friend bool operator==(const mint &lhs, const mint &rhs) { return lhs._v == rhs._v; }
        friend bool operator!=(const mint &lhs, const mint &rhs) { return lhs._v != rhs._v; }

    private:
        unsigned int _v;
        static constexpr unsigned int umod() { return m; }
        static constexpr bool prime = internal::is_prime<m>;
    };

    template<int id>
    struct dynamic_modint : internal::modint_base {
        using mint = dynamic_modint;

    public:
        static int mod() { return (int) (bt.umod()); }
        static void set_mod(int m) {
            assert(1 <= m);
            bt = internal::barrett(m);
        }
        static mint raw(int v) {
            mint x;
            x._v = v;
            return x;
        }

        dynamic_modint() : _v(0) {}
        template<class T, internal::is_signed_int_t<T> * = nullptr>
        dynamic_modint(T v) {
            long long x = (long long) (v % (long long) (mod()));
            if (x < 0)
                x += mod();
            _v = (unsigned int) (x);
        }
        template<class T, internal::is_unsigned_int_t<T> * = nullptr>
        dynamic_modint(T v) {
            _v = (unsigned int) (v % mod());
        }

        int val() const { return _v; }

        mint &operator++() {
            _v++;
            if (_v == umod())
                _v = 0;
            return *this;
        }
        mint &operator--() {
            if (_v == 0)
                _v = umod();
            _v--;
            return *this;
        }
        mint operator++(int) {
            mint result = *this;
            ++*this;
            return result;
        }
        mint operator--(int) {
            mint result = *this;
            --*this;
            return result;
        }

        mint &operator+=(const mint &rhs) {
            _v += rhs._v;
            if (_v >= umod())
                _v -= umod();
            return *this;
        }
        mint &operator-=(const mint &rhs) {
            _v += mod() - rhs._v;
            if (_v >= umod())
                _v -= umod();
            return *this;
        }
        mint &operator*=(const mint &rhs) {
            _v = bt.mul(_v, rhs._v);
            return *this;
        }
        mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }

        mint operator+() const { return *this; }
        mint operator-() const { return mint() - *this; }

        mint pow(long long n) const {
            assert(0 <= n);
            mint x = *this, r = 1;
            while (n) {
                if (n & 1)
                    r *= x;
                x *= x;
                n >>= 1;
            }
            return r;
        }
        mint inv() const {
            auto eg = internal::inv_gcd(_v, mod());
            assert(eg.first == 1);
            return eg.second;
        }

        friend mint operator+(const mint &lhs, const mint &rhs) { return mint(lhs) += rhs; }
        friend mint operator-(const mint &lhs, const mint &rhs) { return mint(lhs) -= rhs; }
        friend mint operator*(const mint &lhs, const mint &rhs) { return mint(lhs) *= rhs; }
        friend mint operator/(const mint &lhs, const mint &rhs) { return mint(lhs) /= rhs; }
        friend bool operator==(const mint &lhs, const mint &rhs) { return lhs._v == rhs._v; }
        friend bool operator!=(const mint &lhs, const mint &rhs) { return lhs._v != rhs._v; }

    private:
        unsigned int _v;
        static internal::barrett bt;
        static unsigned int umod() { return bt.umod(); }
    };
    template<int id>
    internal::barrett dynamic_modint<id>::bt(998244353);

    using modint998244353 = static_modint<998244353>;
    using modint1000000007 = static_modint<1000000007>;
    using modint = dynamic_modint<-1>;

    namespace internal {

        template<class T>
        using is_static_modint = std::is_base_of<internal::static_modint_base, T>;

        template<class T>
        using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;

        template<class>
        struct is_dynamic_modint : public std::false_type {};
        template<int id>
        struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};

        template<class T>
        using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

    } // namespace internal

} // namespace atcoder

using Z = atcoder::static_modint<MOD>;

Z q_pow(Z base, long long exp) {
    Z result(1);
    while (exp > 0) {
        if (exp & 1)
            result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

constexpr int N = 500'005;

struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;

    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    explicit Comb(int n) : Comb() { init(n); }

    void init(int m) {
        if (m <= n) {
            return;
        }
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);

        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }

    Z fac(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) {
            init(2 * m);
        }
        return _inv[m];
    }
    Z C(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fac(n) * invfac(m) * invfac(n - m);
    }
    Z A(int n, int m) {
        if (n < m || m < 0) {
            return 0;
        }
        return fac(n) * invfac(n - m);
    }
} comb(N);

int Multitest = 1;

#define int ll

void init() {}

void solve() {
    int a1, d1, len1;
    rd(a1, d1, len1);
    int a2, d2, len2;
    rd(a2, d2, len2);

    int end1 = a1 + d1 * (len1 - 1);
    int end2 = a2 + d2 * (len2 - 1);

    if (d2 % d1 != 0) {
        prt(0);
        return;
    }

    if ((a2 - a1) % d1 != 0) {
        prt(0);
        return;
    }

    if (a2 < a1 || end2 > end1) {
        prt(0);
        return;
    }

    int t1 = a2 - d2;
    int t2 = end2 + d2;
    if (t1 < a1 || t2 > end1) {
        prt(-1);
        return;
    }

    vi divs;
    for (int i = 1; i * i <= d2; i++) {
        if (d2 % i == 0) {
            divs.pb(i);
            if (d2 / i != i) {
                divs.pb(d2 / i);
            }
        }
    }

    Z ans = 0;
    for (int d: divs) {
        if (d1 / gcd(d1, d) * d == d2) {
            Z left = d2 / d;
            ans += left * left;
        }
    }

    prt(ans.val());
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
