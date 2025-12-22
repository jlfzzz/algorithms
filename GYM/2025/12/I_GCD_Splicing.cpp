#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
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
constexpr int MOD2 = int(1e9 + 7);
constexpr int MOD = int(998244353);
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

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 4e5 + 5;

struct Sieve {
    bool is_not_prime[N + 1]{};
    std::vector<int> primes;
    int min_prime_factor[N + 1]{};
    int distinct_factors_count[N + 1]{}; // 不同质因子个数

    int divisor_count[N + 1]{}; // 约数个数
    int cnt_exp[N + 1]{}; // 最小质因子的指数

    Sieve() { init(N); }

    void init(int n) {
        is_not_prime[0] = is_not_prime[1] = true;
        min_prime_factor[0] = min_prime_factor[1] = 0;
        distinct_factors_count[1] = 0;

        divisor_count[1] = 1;
        cnt_exp[1] = 0;

        for (int i = 2; i <= n; ++i) {
            if (!is_not_prime[i]) {
                primes.push_back(i);
                min_prime_factor[i] = i;
                distinct_factors_count[i] = 1;

                cnt_exp[i] = 1;
                divisor_count[i] = 2;
            }

            for (int p: primes) {
                long long x = 1LL * i * p;
                if (x > n)
                    break;
                is_not_prime[i * p] = true;
                min_prime_factor[i * p] = p;

                if (i % p == 0) {
                    distinct_factors_count[i * p] = distinct_factors_count[i];

                    cnt_exp[i * p] = cnt_exp[i] + 1;
                    divisor_count[i * p] = divisor_count[i] / (cnt_exp[i] + 1) * (cnt_exp[i * p] + 1);

                    break;
                } else {
                    distinct_factors_count[i * p] = distinct_factors_count[i] + 1;

                    cnt_exp[i * p] = 1;
                    divisor_count[i * p] = divisor_count[i] * 2;
                }
            }
        }
    }

    [[nodiscard]] bool is_prime(int x) const {
        if (x <= 1 || x > N)
            return false;
        return !is_not_prime[x];
    }
} sieve;

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);

    vi a(n + 1);
    rv(a, 1);

    int mx = ranges::max(a);
    vi first(mx + 1, 0);
    vector<bool> start(n + 1, false);
    vvi divs(n + 1);

    int c1 = 0;
    int cost = 0;

    F(i, 1, n) {
        int x = a[i];
        if (x == 1) {
            c1++;
            continue;
        }

        while (x > 1) {
            int p = sieve.min_prime_factor[x];
            divs[i].pb(p);
            while (x % p == 0)
                x /= p;
        }

        bool have = false;
        for (int p: divs[i]) {
            if (first[p] != 0) {
                have = true;
            }
        }

        if (!have) {
            start[i] = true;
            cost++;
        }

        for (int p: divs[i]) {
            if (first[p] == 0) {
                first[p] = i;
            }
        }
    }

    int ans = cost + c1;

    F(i, 1, n) {
        if (a[i] == 1)
            continue;

        vi temp;
        int mp = inf;

        for (int p: divs[i]) {
            int k = first[p];
            if (k != 0 && k < i) {
                if (start[k]) {
                    temp.pb(k);
                }
                if (k < mp) {
                    mp = k;
                }
            }
        }

        sort(all(temp));
        temp.erase(unique(all(temp)), temp.end());

        int isStart = start[i] ? 1 : 0;
        int c = SZ(temp);

        int cost1 = cost - isStart + 1 - c;
        ans = min(ans, cost1 + c1);

        if (!start[i]) {
            int cc = 0;
            for (int k: temp) {
                if (k > mp) {
                    cc++;
                }
            }
            int cost2 = cost - cc;
            ans = min(ans, cost2 + c1);
        }
    }

    prt(ans);
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
