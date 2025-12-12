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

struct FFT {
    using cd = complex<double>;
    const double PI = acos(-1);

    vector<int> rev;
    void init_rev(int limit) {
        int bit = 0;
        while ((1 << bit) < limit)
            bit++;

        rev.resize(limit);
        rev[0] = 0;
        for (int i = 1; i < limit; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        }
    }

    void fft(vector<cd> &a, bool invert) {
        int n = a.size();

        if (rev.size() != n) {
            init_rev(n);
        }

        for (int i = 0; i < n; i++) {
            if (i < rev[i]) {
                swap(a[i], a[rev[i]]);
            }
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cd w(1);
                for (int j = 0; j < len / 2; j++) {
                    cd u = a[i + j];
                    cd v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }

        if (invert) {
            for (cd &x: a)
                x /= n;
        }
    }

    vector<long long> multiply(const vector<int> &const_a, const vector<int> &const_b) {
        vector<cd> fa(const_a.begin(), const_a.end());
        vector<cd> fb(const_b.begin(), const_b.end());
        int n = 1;
        while (n < const_a.size() + const_b.size())
            n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++)
            fa[i] *= fb[i];
        fft(fa, true);

        vector<long long> result(n);
        for (int i = 0; i < n; i++)
            result[i] = round(fa[i].real());
        return result;
    }
};

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

ll qpow(ll base, ll exp) {
    ll res = 1;
    base %= MOD2;
    while (exp > 0) {
        if (exp & 1)
            res = (res * base) % MOD2;
        base = (base * base) % MOD2;
        exp >>= 1;
    }
    return res;
}

void solve() {
    string s;
    rd(s);
    int n = s.size();

    vector<int> va(n), vb(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a')
            va[i] = 1;
        else
            vb[i] = 1;
    }

    FFT fft;
    vector<long long> resA = fft.multiply(va, va);
    vector<long long> resB = fft.multiply(vb, vb);

    ll total_ans = 0;
    int max_len = resA.size();

    for (int i = 0; i <= 2 * n - 2; i++) {
        if (i >= max_len)
            break;

        long long pairs = resA[i] + resB[i];
        long long cnt = (pairs + 1) / 2;

        total_ans = (total_ans + qpow(2, cnt) - 1 + MOD2) % MOD2;
    }

    string t = "$#";
    for (char c: s) {
        t += c;
        t += "#";
    }

    int m = t.size();
    vector<int> p(m, 0);
    int mx = 0, id = 0;
    ll continuous_palindromes = 0;

    for (int i = 1; i < m; i++) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (i + p[i] < m && i - p[i] >= 0 && t[i + p[i]] == t[i - p[i]]) {
            p[i]++;
        }
        if (i + p[i] > mx) {
            mx = i + p[i];
            id = i;
        }
        continuous_palindromes = (continuous_palindromes + p[i] / 2) % MOD2;
    }

    ll final_ans = (total_ans - continuous_palindromes + MOD2) % MOD2;
    prt(final_ans);
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
