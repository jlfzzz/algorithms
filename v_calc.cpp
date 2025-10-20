#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace utils {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
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
    void prt_vec(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v, int start_index) {
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
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
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

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);
    const int MAXV = 1 << 10; // 1024
    vector<int> A(n + 1), L(n + 1), R(n + 1);
    for (int i = 1; i <= n; i++) {
        int ai, li, ri;
        rd(ai, li, ri);
        A[i] = ai;
        L[i] = li;
        R[i] = ri;
    }

    auto addmod = [](int a, int b) -> int {
        a += b;
        if (a >= MOD)
            a -= MOD;
        return a;
    };
    auto submod = [](int a, int b) -> int {
        a -= b;
        if (a < 0)
            a += MOD;
        return a;
    };
    auto mulmod = [](int a, int b) -> int { return (int) ((__int128) a * b % MOD); };
    auto qpow = [&](int a, long long e) -> int {
        int r = 1;
        while (e) {
            if (e & 1)
                r = mulmod(r, a);
            a = mulmod(a, a);
            e >>= 1;
        }
        return r;
    };

    auto fwt_xor = [&](vector<int> &f, bool inverse) {
        for (int len = 1; len < MAXV; len <<= 1) {
            for (int i = 0; i < MAXV; i += (len << 1)) {
                for (int j = 0; j < len; j++) {
                    int u = f[i + j];
                    int v = f[i + j + len];
                    f[i + j] = addmod(u, v);
                    f[i + j + len] = submod(u, v);
                }
            }
        }
        if (inverse) {
            int invN = qpow(MAXV % MOD, MOD - 2);
            for (int &x: f)
                x = mulmod(x, invN);
        }
    };

    auto xor_convolution = [&](const vector<int> &a, const vector<int> &b) {
        vector<int> fa = a, fb = b;
        fwt_xor(fa, false);
        fwt_xor(fb, false);
        for (int i = 0; i < MAXV; i++)
            fa[i] = mulmod(fa[i], fb[i]);
        fwt_xor(fa, true);
        return fa;
    };

    // dp over odd positions: dp holds distribution for current odd value
    vector<int> dp(MAXV, 0);
    for (int x = 0; x <= A[1]; x++)
        dp[x] = 1;
    if (n == 1) {
        int ans = 0;
        for (int v: dp)
            ans = addmod(ans, v);
        prt(ans);
        return;
    }

    // iterate over even i = 2,4,...,n-1
    for (int i = 2; i < n; i += 2) {
        int Aodd_prev = A[i - 1];
        int Aeven = A[i];
        int Aodd_next = A[i + 1];
        // mask for [L,R] on distance domain
        vector<int> mask(MAXV, 0);
        for (int d = L[i]; d <= R[i]; d++)
            mask[d] = 1;

        // prefix sums of dp for fast h[d]
        vector<int> pref(MAXV + 1, 0);
        for (int x = 0; x < MAXV; x++) {
            pref[x + 1] = addmod(pref[x], dp[x]);
        }
        auto sum_dp = [&](int l, int r) -> int {
            if (l > r)
                return 0;
            l = max(0LL, l);
            r = min((long long) MAXV - 1, r);
            if (l > r)
                return 0;
            return submod(pref[r + 1], pref[l]);
        };

        vector<int> h(MAXV, 0);
        // compute h[d] = sum_x dp[x] * cnt_d(x)
        for (int d = 0; d < MAXV; d++) {
            int val = 0;
            if (d == 0) {
                // x in [0..Aeven]
                val = addmod(val, sum_dp(0, Aeven));
            } else {
                // x in [0..Aeven]
                int two_part = 0;
                if (Aeven - d >= d) {
                    two_part = sum_dp(d, Aeven - d);
                    two_part = addmod(two_part, two_part); // *2
                }
                int left_border = sum_dp(0, min(d - 1, (int) Aeven));
                int right_border = sum_dp((int) Aeven - d + 1, (int) Aeven);
                // x in (Aeven .. Aodd_prev]
                int high_l = max((int) Aeven + 1, d);
                int high_r = min((int) Aodd_prev, (int) Aeven + d);
                int high_part = sum_dp(high_l, high_r);
                val = addmod(addmod(addmod(two_part, left_border), right_border), high_part);
            }
            h[d] = val;
        }

        vector<int> dp_next = xor_convolution(h, mask);
        // enforce next odd bound
        for (int z = 0; z < MAXV; z++) {
            if (z > Aodd_next)
                dp_next[z] = 0;
        }
        dp.swap(dp_next);
    }

    int ans = 0;
    for (int v: dp)
        ans = addmod(ans, v);
    if (n % 2 == 0) {
        ans = mulmod(ans, (A[n] + 1) % MOD);
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
