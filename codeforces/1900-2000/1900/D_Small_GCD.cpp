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

constexpr int N = 1e5 + 5;

struct EulerSieve {
public:
    int n;
    vector<int> phi;
    vector<int> mu;
    vector<int> nextp; // min prime factor
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

int Multitest = 1;

vi divs[N];
int cnt[N];

void init() {
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }
    for (int i = 1; i < N; i++) {
        reverse(all(divs[i]));
    }
}

void solve2() {
    int n;
    rd(n);
    vi a(n);
    rv(a, 0);
    sort(all(a));

    ll ans = 0;
    for (int j = 0; j < n; j++) {
        int val = a[j];
        ll sum = 0;
        for (int d: divs[val]) {
            sum += 1LL * sieve.get_phi(d) * cnt[d];
        }
        ans += sum * (n - 1 - j);
        for (int d: divs[val]) {
            cnt[d]++;
        }
    }

    prt(ans);

    for (int x: a) {
        for (int d: divs[x]) {
            cnt[d]--;
        }
    }
}

ll f[N];
int g[N];

void solve() {
    int n;
    rd(n);
    vector<int> a(n);
    rv(a);
    sort(all(a));

    ll ans = 0;
    F(i, 0, n - 1) {
        int val = a[i];
        ll sum_gcd = 0;

        for (int u: divs[val]) {
            f[u] = g[u];
            for (int v: divs[val / u]) {
                if (v == 1)
                    continue;
                f[u] -= f[u * v];
            }

            sum_gcd += (ll) u * f[u];
        }

        ans += sum_gcd * (n - 1 - i);

        for (int u: divs[val]) {
            g[u]++;
        }
    }

    prt(ans);

    for (int x: a) {
        for (int u: divs[x]) {
            g[u]--;
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
