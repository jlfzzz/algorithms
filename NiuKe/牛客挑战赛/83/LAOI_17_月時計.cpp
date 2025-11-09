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

using Z = atcoder::static_modint<MOD2>;

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

namespace atcoder {
    namespace internal {

#if __cplusplus >= 202002L

        using std::bit_ceil;

#else

        unsigned int bit_ceil(unsigned int n) {
            unsigned int x = 1;
            while (x < (unsigned int) (n))
                x *= 2;
            return x;
        }

#endif

        int countr_zero(unsigned int n) {
#ifdef _MSC_VER
            unsigned long index;
            _BitScanForward(&index, n);
            return index;
#else
            return __builtin_ctz(n);
#endif
        }

        constexpr int countr_zero_constexpr(unsigned int n) {
            int x = 0;
            while (!(n & (1 << x)))
                x++;
            return x;
        }

    } // namespace internal

#if __cplusplus >= 201703L

    template<class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
    struct lazy_segtree {
        static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>, "op must work as S(S, S)");
        static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, "e must work as S()");
        static_assert(std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>, "mapping must work as S(F, S)");
        static_assert(std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
                      "composition must work as F(F, F)");
        static_assert(std::is_convertible_v<decltype(id), std::function<F()>>, "id must work as F()");

#else

    template<class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
    struct lazy_segtree {

#endif

    public:
        lazy_segtree() : lazy_segtree(0) {}
        explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
        explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size())) {
            size = (int) internal::bit_ceil((unsigned int) (_n));
            log = internal::countr_zero((unsigned int) size);
            d = std::vector<S>(2 * size, e());
            lz = std::vector<F>(size, id());
            for (int i = 0; i < _n; i++)
                d[size + i] = v[i];
            for (int i = size - 1; i >= 1; i--) {
                update(i);
            }
        }

        void set(int p, S x) {
            assert(0 <= p && p < _n);
            p += size;
            for (int i = log; i >= 1; i--)
                push(p >> i);
            d[p] = x;
            for (int i = 1; i <= log; i++)
                update(p >> i);
        }

        S get(int p) {
            assert(0 <= p && p < _n);
            p += size;
            for (int i = log; i >= 1; i--)
                push(p >> i);
            return d[p];
        }

        S prod(int l, int r) {
            assert(0 <= l && l <= r && r <= _n);
            if (l == r)
                return e();

            l += size;
            r += size;

            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l)
                    push(l >> i);
                if (((r >> i) << i) != r)
                    push((r - 1) >> i);
            }

            S sml = e(), smr = e();
            while (l < r) {
                if (l & 1)
                    sml = op(sml, d[l++]);
                if (r & 1)
                    smr = op(d[--r], smr);
                l >>= 1;
                r >>= 1;
            }

            return op(sml, smr);
        }

        S all_prod() { return d[1]; }

        void apply(int p, F f) {
            assert(0 <= p && p < _n);
            p += size;
            for (int i = log; i >= 1; i--)
                push(p >> i);
            d[p] = mapping(f, d[p]);
            for (int i = 1; i <= log; i++)
                update(p >> i);
        }
        void apply(int l, int r, F f) {
            assert(0 <= l && l <= r && r <= _n);
            if (l == r)
                return;

            l += size;
            r += size;

            for (int i = log; i >= 1; i--) {
                if (((l >> i) << i) != l)
                    push(l >> i);
                if (((r >> i) << i) != r)
                    push((r - 1) >> i);
            }

            {
                int l2 = l, r2 = r;
                while (l < r) {
                    if (l & 1)
                        all_apply(l++, f);
                    if (r & 1)
                        all_apply(--r, f);
                    l >>= 1;
                    r >>= 1;
                }
                l = l2;
                r = r2;
            }

            for (int i = 1; i <= log; i++) {
                if (((l >> i) << i) != l)
                    update(l >> i);
                if (((r >> i) << i) != r)
                    update((r - 1) >> i);
            }
        }

        template<bool (*g)(S)>
        int max_right(int l) {
            return max_right(l, [](S x) { return g(x); });
        }
        template<class G>
        int max_right(int l, G g) {
            assert(0 <= l && l <= _n);
            assert(g(e()));
            if (l == _n)
                return _n;
            l += size;
            for (int i = log; i >= 1; i--)
                push(l >> i);
            S sm = e();
            do {
                while (l % 2 == 0)
                    l >>= 1;
                if (!g(op(sm, d[l]))) {
                    while (l < size) {
                        push(l);
                        l = (2 * l);
                        if (g(op(sm, d[l]))) {
                            sm = op(sm, d[l]);
                            l++;
                        }
                    }
                    return l - size;
                }
                sm = op(sm, d[l]);
                l++;
            } while ((l & -l) != l);
            return _n;
        }

        template<bool (*g)(S)>
        int min_left(int r) {
            return min_left(r, [](S x) { return g(x); });
        }
        template<class G>
        int min_left(int r, G g) {
            assert(0 <= r && r <= _n);
            assert(g(e()));
            if (r == 0)
                return 0;
            r += size;
            for (int i = log; i >= 1; i--)
                push((r - 1) >> i);
            S sm = e();
            do {
                r--;
                while (r > 1 && (r % 2))
                    r >>= 1;
                if (!g(op(d[r], sm))) {
                    while (r < size) {
                        push(r);
                        r = (2 * r + 1);
                        if (g(op(d[r], sm))) {
                            sm = op(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                sm = op(d[r], sm);
            } while ((r & -r) != r);
            return 0;
        }

    private:
        int _n, size, log;
        std::vector<S> d;
        std::vector<F> lz;

        void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
        void all_apply(int k, F f) {
            d[k] = mapping(f, d[k]);
            if (k < size)
                lz[k] = composition(f, lz[k]);
        }
        void push(int k) {
            all_apply(2 * k, lz[k]);
            all_apply(2 * k + 1, lz[k]);
            lz[k] = id();
        }
    };

} // namespace atcoder

struct Matrix {
    Z a[3][3];

    Matrix() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                a[i][j] = 0;
    }

    static Matrix identity() {
        Matrix e;
        for (int i = 0; i < 3; i++)
            e.a[i][i] = 1;
        return e;
    }

    friend Matrix operator*(const Matrix &A, const Matrix &B) {
        Matrix C;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                for (int k = 0; k < 3; k++) {
                    C.a[i][k] += A.a[i][j] * B.a[j][k];
                }
        return C;
    }
};

vl operator*(const Matrix &M, const vl &V) {
    vl R(3, 0);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            R[i] += M.a[i][j].val() * V[j];
        }
    R[0] %= MOD2;
    R[1] %= MOD2;
    R[2] %= MOD2;
    return R;
}

Z dot(const Z V1[3], const Z V2[3]) { return V1[0] * V2[0] + V1[1] * V2[1] + V1[2] * V2[2]; }

using S = Matrix;
using F = int;

S op(S a, S b) { return b * a; }

S e() { return Matrix::identity(); }

S mapping(F f, S x) { return x; }

F composition(F f, F g) { return 0; }

F id() { return 0; }

constexpr int N = 1e6 + 5;
int a[N];

Matrix build_matrix(int i) {
    Matrix M;
    int v = a[i];
    Z w1 = (v == 0 || v == 1) ? 1 : 0;
    Z w2 = (v == 0 || v == 2) ? 1 : 0;
    Z w3 = (v == 0 || v == 3) ? 1 : 0;

    M.a[0][0] = w1;
    M.a[0][1] = w1;
    M.a[0][2] = w1;
    M.a[1][0] = w2;
    M.a[1][1] = w2;
    M.a[1][2] = 0;
    M.a[2][0] = 0;
    M.a[2][1] = w3;
    M.a[2][2] = w3;
    return M;
}

int Multitest = 0;

void init() {}

void solve() {
    int n, q;
    rd(n, q);
    for (int i = 1; i <= n; i++)
        rd(a[i]);

    vector<S> initial_matrices(n);
    for (int i = 0; i < n; i++) {
        initial_matrices[i] = build_matrix(i + 1);
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(initial_matrices);

    while (q--) {
        int op_type;
        rd(op_type);
        if (op_type == 1) {
            int x, y;
            rd(x, y);
            a[x] = y;
            seg.set(x - 1, build_matrix(x));
        } else {
            int l, r;
            rd(l, r);

            if (l == r) {
                Z ans = (a[l] == 0 || a[l] == 3) ? 1 : 0;
                prt(ans.val());
                continue;
            }

            Z Vl[3];
            Vl[0] = (a[l] == 0 || a[l] == 1) ? 1 : 0;
            Vl[1] = 0;
            Vl[2] = (a[l] == 0 || a[l] == 3) ? 1 : 0;

            Matrix M_range = seg.prod(l, r);

            Z Vr[3];
            Vr[0] = M_range.a[0][0] * Vl[0] + M_range.a[0][1] * Vl[1] + M_range.a[0][2] * Vl[2];
            Vr[1] = M_range.a[1][0] * Vl[0] + M_range.a[1][1] * Vl[1] + M_range.a[1][2] * Vl[2];
            Vr[2] = M_range.a[2][0] * Vl[0] + M_range.a[2][1] * Vl[1] + M_range.a[2][2] * Vl[2];


            Z ans = Vr[1] + Vr[2];
            prt(ans.val());
        }
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
