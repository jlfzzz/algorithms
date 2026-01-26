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
#define us unsigned
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

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

long long qpow(long long base, long long exp) {
    long long res = 1;
    while (exp > 0) {
        if (exp & 1)
            res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

long long fac[N], invFac[N];
bool inited_fac = false;

void prepare_fac(int n) {
    if (inited_fac)
        return;
    fac[0] = 1;
    F(i, 1, n) fac[i] = fac[i - 1] * i % MOD;
    invFac[n] = qpow(fac[n], MOD - 2);
    D(i, n - 1, 0) invFac[i] = invFac[i + 1] * (i + 1) % MOD;
    inited_fac = true;
}

int sumR[1 << 17], sumB[1 << 17];
long long f[1 << 17];

void solve() {
    int n, m;
    rd(n, m);

    prepare_fac(m);

    int limit = 1 << n;

    vector<int> r_deg(n), b_deg(n);
    F(i, 1, m) {
        int u;
        rd(u);
        --u;
        r_deg[u]++;
    }
    F(i, 1, m) {
        int u;
        rd(u);
        --u;
        b_deg[u]++;
    }

    for (int mask = 1; mask < limit; ++mask) {
        int lb = mask & -mask;
        int idx = __builtin_ctz(lb);
        int prev = mask ^ lb;
        sumR[mask] = sumR[prev] + r_deg[idx];
        sumB[mask] = sumB[prev] + b_deg[idx];
    }

    for (int mask = 1; mask < limit; ++mask) {
        if (sumR[mask] != sumB[mask])
            continue;

        long long g = fac[sumR[mask]];
        long long res = g;

        int pivot = mask & -mask;
        int other = mask ^ pivot;

        for (int sub = other; sub > 0; sub = (sub - 1) & other) {
            if (sumR[sub] == sumB[sub]) {
                long long term = f[mask ^ sub] * fac[sumR[sub]] % MOD;
                res = (res - term + MOD) % MOD;
            }
        }

        f[mask] = res;
    }

    long long ans = 0;
    for (int mask = 1; mask < limit; ++mask) {
        if (sumR[mask] == sumB[mask] && f[mask] > 0) {
            long long outside_ways = fac[m - sumR[mask]];
            ans = (ans + f[mask] * outside_ways) % MOD;
        }
    }

    prt(ans * invFac[m] % MOD);
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
