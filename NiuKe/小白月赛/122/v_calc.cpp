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

constexpr int MAX = 1 << 10;
constexpr int MAX_BIT = 10;

void Add(ll &x, ll y) {
    x += y;
    if (x >= MOD) {
        x -= MOD;
    }
    if (x < 0) {
        x += MOD;
    }
}

vector<array<ll, 2>> GetSegXOR(ll x, ll y) {
    vector<array<ll, 2>> seg;
    if (y < 0) {
        return seg;
    }
    ll p = 0;
    for (ll i = MAX_BIT - 1; i >= 0; i--) {
        if ((y >> i) & 1LL) {
            if ((x >> i) & 1LL) {
                seg.push_back({p | (1LL << i), p | ((1LL << (i + 1)) - 1)});
            } else {
                seg.push_back({p, p | ((1LL << i) - 1)});
                p |= (1LL << i);
            }
        } else {
            if ((x >> i) & 1LL) {
                p |= (1LL << i);
            }
        }
    }
    assert((p ^ x) == y);
    seg.push_back({p, p});
    return seg;
}

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
    cin >> n;
    vector<int> A(n + 1), L(n + 1), R(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> A[i] >> L[i] >> R[i];
    }
    vector<int> dp(MAX);
    for (int v = 0; v <= A[1]; v++) {
        Add(dp[v], 1);
    }
    for (int i = 2; i <= n; i++) {
        vector<int> ndp(MAX);
        for (int j = 0; j < MAX; j++) {
            if (dp[j] == 0) {
                continue;
            }
            if (i % 2 == 0) {
                if (j >= A[i]) {
                    Add(ndp[j - A[i]], dp[j]);
                    if (j + 1 < MAX) {
                        Add(ndp[j + 1], -dp[j]);
                    }
                } else {
                    Add(ndp[0], dp[j]);
                    if (j + 1 < MAX) {
                        Add(ndp[j + 1], -dp[j]);
                    }
                    Add(ndp[1], dp[j]);
                    if (A[i] - j + 1 < MAX) {
                        Add(ndp[A[i] - j + 1], -dp[j]);
                    }
                }
            } else {
                auto segl = GetSegXOR(j, L[i - 1] - 1);
                auto segr = GetSegXOR(j, R[i - 1]);
                for (auto &pr: segr) {
                    int l = pr[0];
                    int r = pr[1];
                    l = max<int>(0, l);
                    r = min<int>(r, A[i]);
                    if (l > r) {
                        continue;
                    }
                    Add(ndp[l], dp[j]);
                    if (r + 1 < MAX) {
                        Add(ndp[r + 1], -dp[j]);
                    }
                }
                for (auto &pr: segl) {
                    int l = pr[0];
                    int r = pr[1];
                    l = max<int>(0, l);
                    r = min<int>(r, A[i]);
                    if (l > r) {
                        continue;
                    }
                    Add(ndp[l], -dp[j]);
                    if (r + 1 < MAX) {
                        Add(ndp[r + 1], dp[j]);
                    }
                }
            }
        }
        for (int j = 1; j < MAX; j++) {
            Add(ndp[j], ndp[j - 1]);
        }
        dp.swap(ndp);
    }
    int ans = 0;
    for (int i = 0; i < MAX; i++) {
        Add(ans, dp[i]);
    }
    cout << ans << '\n';
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
