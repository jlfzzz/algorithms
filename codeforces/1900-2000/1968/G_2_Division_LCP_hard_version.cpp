#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
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

mt19937 rng(random_device{}());

int rnd(long long x, long long y) { return uniform_int_distribution<int>(x, y)(rng); }

long long MOD = 1e18 + rnd(0, 1e9);
int BASE = 233 + rnd(0, 1e3);

struct HashSeq {
    int n;
    vector<__int128> P, H, HR;

    HashSeq(string s) {
        n = s.size();
        P.resize(n + 1);
        P[0] = 1;
        for (int i = 1; i <= n; i++)
            P[i] = P[i - 1] * BASE % MOD;

        H.resize(n + 1);
        H[0] = 0;
        for (int i = 1; i <= n; i++)
            H[i] = (H[i - 1] * BASE + (s[i - 1] ^ 7)) % MOD;

        HR.resize(n + 1);
        HR[0] = 0;
        for (int i = 1; i <= n; i++) {
            HR[i] = (HR[i - 1] * BASE + (s[n - i] ^ 7)) % MOD;
        }
    }

    long long query(int l, int r) const {
        if (l > r)
            return 0;
        __int128 res = (H[r] - (H[l - 1] * P[r - l + 1]) % (__int128) MOD);
        long long ans = (long long) ((res + (__int128) MOD) % (__int128) MOD);
        return ans;
    }

    long long query_rev_on_reversed(int l, int r) const {
        if (l > r)
            return 0;
        __int128 res = (HR[r] - (HR[l - 1] * P[r - l + 1]) % (__int128) MOD);
        return (long long) ((res + (__int128) MOD) % (__int128) MOD);
    }

    long long query_rev_sub(int l, int r) const {
        if (l > r)
            return 0;
        int L = n - r + 1;
        int R = n - l + 1;
        __int128 res = (HR[R] - (HR[L - 1] * P[R - L + 1]) % (__int128) MOD);
        return (long long) ((res + (__int128) MOD) % (__int128) MOD);
    }
};

#define int ll

int Multitest = 1;

void init() {}

void solve() {
    int n, l, r;
    rd(n, l, r);

    string s;
    rd(s);

    HashSeq hs(s);

    vector<int> ANS(n + 1);
    vector<int> mem(n + 1, -1);

    int B = ceil(sqrt(n));

    vector<int> z(n, 0);
    if (n >= 1) {
        int L = 0, R = 0;
        for (int i = 1; i < n; i++) {
            if (i <= R)
                z[i] = min(R - i + 1, z[i - L]);
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                z[i]++;
            if (i + z[i] - 1 > R) {
                L = i;
                R = i + z[i] - 1;
            }
        }
        z[0] = n;
    }

    auto check = [&](int len) -> int {
        if (len > n) {
            return 0;
        }
        if (mem[len] != -1)
            return mem[len];
        int seg = 1;

        int i = len + 1;
        while (i <= n) {
            int r = i + len - 1;
            if (r > n) {
                break;
            }

            if (z[i - 1] >= len) {
                i = r + 1;
                seg++;
            } else {
                i++;
            }
        }

        return mem[len] = seg;
    };

    for (int t: range(min(B, r - l + 1))) {
        int target = l + t;
        int lo = 1;
        int hi = n / target + 1;
        int ans = 0;

        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (check(mid) >= target) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }

        ANS[target] = ans;
    }

    for (int len = 1; len <= B; len++) {
        int seg = check(len);
        if (seg >= 1) {
            int idx = min(seg, n);
            ANS[idx] = max(ANS[idx], len);
        }
    }

    for (int i = n - 1; i >= 1; i--) {
        ANS[i] = max(ANS[i], ANS[i + 1]);
    }

    for (int i: range(l, r + 1)) {
        cout << ANS[i] << ' ';
    }
    cout << '\n';
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
