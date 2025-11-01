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
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

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
} // namespace utils

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

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

void solve() {
    string a, b;
    rd(a, b);

    int n = a.size();
    auto t = a + a;
    HashSeq s1(t), s2(b);

    // if (s1.query(1, n) == s2.query(1, n)) {
    //     prt(0);
    //     return;
    // }

    auto valB = s2.query(1, n);

    F(i, 1, n) {
        auto val = s1.query(i, i + n - 1);
        if (val == valB) {
            prt(i - 1);
            return;
        }
    }
    prt(-1);
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
