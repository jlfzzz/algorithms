#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace io {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
    }

    template<typename... Args>
    void prt(const Args &...args) {
        ((cout << args << " "), ...);
        cout << "\n";
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

    template<typename End, typename... Args>
    void prt_end(const End &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename... Args>
    void prt_endl(const Args &...args) {
        ((cout << args << " "), ...);
        cout << endl;
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
} // namespace io

using namespace io;

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);
    vector<int> a(n), b(n);
    rd_vec(a);
    rd_vec(b);

    vector<int> pre(n + 1);
    For(i, n) { pre[i + 1] = pre[i] + a[i] + b[i]; }

    vector<int> dp(pre[n] + 1, inf);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        int A = a[i];
        int B = b[i];
        vector<int> ndp(pre[n] + 1, inf);
        for (int j = 0; j <= pre[n]; j++) {
            if (dp[j] == inf)
                continue;
            if (j + A <= pre[n])
                ndp[j + A] = min(ndp[j + A], dp[j] + A * j + B * (pre[i] - j));
            if (j + B <= pre[n])
                ndp[j + B] = min(ndp[j + B], dp[j] + B * j + A * (pre[i] - j));
        }
        dp.swap(ndp);
    }

    int ans = ranges::min(dp) * 2;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans += a[i] * a[i] + a[j] * a[j] + b[i] * b[i] + b[j] * b[j];
        }
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
