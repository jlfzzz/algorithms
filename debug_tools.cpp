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

#define dbg(...) cerr << "[line: " << __LINE__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)

namespace helpers {
    ostream &operator<<(ostream &os, i128 x) {
        if (x == 0) {
            os << '0';
            return os;
        }
        if (x < 0) {
            os << '-';
            x = -x;
        }
        char buf[64];
        int pos = 0;
        while (x > 0) {
            buf[pos++] = '0' + x % 10;
            x /= 10;
        }
        while (pos--) {
            os << buf[pos];
        }
        return os;
    }

    // 辅助函数：递归打印树的子节点
    void printTreeHelper(int u, int parent, const vector<vector<int>> &adj, string prefix, bool isLast) {
        cout << prefix;
        cout << (isLast ? "└── " : "├── ");
        cout << u << endl;

        // 获取子节点
        vector<int> children;
        for (int v: adj[u]) {
            if (v != parent) {
                children.push_back(v);
            }
        }

        // 递归打印子节点
        for (int i = 0; i < children.size(); i++) {
            bool last = (i == children.size() - 1);
            string newPrefix = prefix + (isLast ? "    " : "│   ");
            printTreeHelper(children[i], u, adj, newPrefix, last);
        }
    }

    // 封装的打印树函数
    // 参数：n - 节点数，edges - 边的列表，root - 根节点（默认为1）
    void printTree(int n, const vector<pair<int, int>> &edges, int root = 1) {
        // 构建邻接表
        vector<vector<int>> adj(n + 1);
        for (const auto &edge: edges) {
            int u = edge.first;
            int v = edge.second;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // 打印树结构
        cout << "Tree structure (root = " << root << "):" << endl;
        cout << root << endl;

        // 获取根节点的所有子节点
        vector<int> children;
        for (int v: adj[root]) {
            children.push_back(v);
        }

        // 打印所有子树
        for (int i = 0; i < children.size(); i++) {
            bool last = (i == children.size() - 1);
            printTreeHelper(children[i], root, adj, "", last);
        }
    }

    // 随机数组
    vector<ll> random_array(int n, int lo, int hi) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<ll> dist(lo, hi);

        vector<ll> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = (ll) dist(gen);
        }
        return arr;
    }

    // 打印整数的二进制表示
    template<typename T>
    void prt_bin(T x, int width = -1, char fill = '0') {
        static_assert(is_integral_v<T>, "prt_bin only supports integral types");

        string s;
        if (x == 0) {
            s = "0";
        } else {
            while (x != 0) {
                s.push_back((x & 1) ? '1' : '0');
                x >>= 1;
            }
            reverse(s.begin(), s.end());
        }

        // 如果指定了宽度，则填充
        if (width > 0 && (int) s.size() < width) {
            s = string(width - s.size(), fill) + s;
        }

        cout << s << "\n";
    }

    // 打印向量vector的二进制
    template<typename T>
    void prt_vec_bin(const vector<T> &v, int width = -1, char fill = '0') {
        for (size_t i = 0; i < v.size(); i++) {
            prt_bin(v[i], width, fill);
        }
    }

    // 输入二进制字符串打印整数
    template<typename T = long long>
    void prt_int(const string &s) {
        static_assert(is_integral_v<T>, "prt_int only supports integral types");
        T x = 0;
        for (char c: s) {
            if (c != '0' && c != '1') {
                throw invalid_argument("Input string must be binary (0/1 only)");
            }
            x = (x << 1) | (c - '0');
        }
        cout << x << "\n";
    }

} // namespace helpers

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
    template<int m>
    ostream &operator<<(ostream &os, const static_modint<m> &x) {
        return os << x.val();
    }
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

namespace math {
    // 组合数
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
    } comb(100'005);

    // 质因数分解
    vector<int> decompose(int x) {
        vector<int> primes;
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                primes.push_back(i);
                while (x % i == 0) {
                    x /= i;
                }
            }
        }
        if (x > 1) {
            primes.push_back(x);
        }
        return primes;
    }

    // 二分判断完全平方数
    bool isPerfectSquare(long long n) {
        if (n < 0)
            return false;
        long long lo = 0, hi = n;
        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            long long sq = mid * mid;
            if (sq == n)
                return true;
            else if (sq < n)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return false;
    }

    i128 getGcd(i128 a, i128 b) {
        while (b != 0) {
            i128 t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    i128 getLcm(i128 x, i128 y) {
        if (x == 0 || y == 0)
            return 0;
        return x / getGcd(x, y) * y;
    }
} // namespace math

class BigInt {
    std::vector<int> digits;
    static const int BASE = 1000000000; // 10^9

public:
    BigInt() : digits(1, 0) {}

    BigInt(int x) {
        if (x == 0)
            digits = {0};
        else {
            while (x > 0) {
                digits.push_back(x % BASE);
                x /= BASE;
            }
        }
    }

    BigInt &operator=(int x) {
        digits.clear();
        if (x == 0)
            digits = {0};
        else {
            while (x > 0) {
                digits.push_back(x % BASE);
                x /= BASE;
            }
        }
        return *this;
    }

    BigInt &operator*=(int x) {
        ll carry = 0;
        for (int i = 0; i < digits.size(); i++) {
            carry += (ll) digits[i] * x;
            digits[i] = carry % BASE;
            carry /= BASE;
        }
        while (carry > 0) {
            digits.push_back(carry % BASE);
            carry /= BASE;
        }
        return *this;
    }

    BigInt operator*(int x) const {
        BigInt res = *this;
        res *= x;
        return res;
    }

    // 除法（返回商）
    BigInt operator/(int x) const {
        BigInt res;
        res.digits.resize(digits.size());
        ll rem = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            rem = rem * BASE + digits[i];
            res.digits[i] = rem / x;
            rem %= x;
        }
        // 去除前导零
        while (res.digits.size() > 1 && res.digits.back() == 0) {
            res.digits.pop_back();
        }
        return res;
    }

    bool operator>(const BigInt &other) const {
        if (digits.size() != other.digits.size()) {
            return digits.size() > other.digits.size();
        }
        for (int i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i]) {
                return digits[i] > other.digits[i];
            }
        }
        return false;
    }

    // 转换为 long long（注意可能溢出）
    operator long long() const {
        long long res = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            res = res * BASE + digits[i];
        }
        return res;
    }

    // 输出
    friend ostream &operator<<(ostream &os, const BigInt &num) {
        os << num.digits.back();
        for (int i = num.digits.size() - 2; i >= 0; i--) {
            os << setw(9) << setfill('0') << num.digits[i];
        }
        return os;
    }
};

using namespace utils;
using namespace helpers;
using namespace math;

vector<pii> readTree(int n);

#define int ll

void func1() {
    int n = 100;

    vector<int> arr = {12, 3, 20, 5, 80, 1};
    auto random_arr1 = random_array(n, 1, 1e5);
    auto random_arr2 = random_array(n, 1, 1e7);

    i128 c = 3;
    prt_bin((int) c);
    F(a, 1, 1000) {
        F(b, 1, 1000) {
            if ((a ^ c) + (b ^ c) == getLcm(a, c) + getLcm(b, c)) {
                prt(a, b);
            }
        }
    }
}

vector<pii> readTree(int n) {
    vector<pii> edges;
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        edges.pb(u, v);
    }
    return edges;
}

signed main() { func1(); }
