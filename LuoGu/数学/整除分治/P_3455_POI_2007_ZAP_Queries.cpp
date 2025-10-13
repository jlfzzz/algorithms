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

constexpr int N = 1'000'005;

struct EulerSieve {
public:
    int n;
    vector<int> phi;
    vector<int> mu;
    vector<int> nextp; // next min prime
    vector<int> prime;
    vector<char> is_prime;

    EulerSieve() : n(0) {}
    EulerSieve(int n) : n(n) { init(n); }

    void init(int n) {
        phi.assign(n, 1);
        mu.assign(n, 1);
        nextp.assign(n, 1);
        is_prime.assign(n, true);
        prime.clear();
        prime.reserve(1.2 * n / log(n));

        is_prime[1] = false;
        phi[1] = 1;
        mu[1] = 1;
        nextp[1] = 1;

        for (int i = 2; i < n; i++) {
            if (is_prime[i]) {
                prime.push_back(i);
                phi[i] = i - 1;
                mu[i] = -1;
                nextp[i] = i;
            }
            for (int j = 0; j < (int) prime.size() && 1LL * i * prime[j] < n; j++) {
                int p = prime[j];
                int num = i * p;
                is_prime[num] = false;
                nextp[num] = p;
                if (i % p == 0) {
                    phi[num] = phi[i] * p;
                    mu[num] = 0;
                    break;
                } else {
                    phi[num] = phi[i] * (p - 1);
                    mu[num] = -mu[i];
                }
            }
        }
    }

    int get_Phi(int x) const {
        int res = x;
        for (int p = 2; x != 1; p += 1) {
            if (x % p == 0) {
                res = res / p * (p - 1);
                while (x % p == 0) {
                    x /= p;
                }
            }
        }
        return res;
    }

    int get_phi(int x) const { return phi[x]; }

    int get_mu(int x) const { return mu[x]; }

    int get_nextp(int x) const { return nextp[x]; }

    bool isprime(int x) const { return is_prime[x]; }

    const vector<int> &get_primes() const { return prime; }
} sieve(N);

#define int ll

int Multitest = 1;

int mu[N];

void init() {
    mu[0] = sieve.mu[0];
    for (int i: range(1, N)) {
        mu[i] = mu[i - 1] + sieve.mu[i];
    }
}

void solve() {
    int a, b, d;
    rd(a, b, d);

    int n = a / d;
    int m = b / d;

    int ans = 0;
    for (int l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += (mu[r] - mu[l - 1]) * (n / l) * (m / l);
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
