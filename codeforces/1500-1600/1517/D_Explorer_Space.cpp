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
constexpr int MOD2 = int(998244353);
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

int Multitest = 0;

void init() {}



void solve() {
    int n, m, k;
    rd(n, m, k);

    vector<vector<int>> hor(n, vector<int>(m - 1));
    vector<vector<int>> ver(n - 1, vector<int>(m));

    For(i, n) {
        For(j, m - 1) { rd(hor[i][j]); }
    }

    For(i, n - 1) {
        For(j, m) { rd(ver[i][j]); }
    }

    if (k % 2) {
        For(i, n) {
            For(j, m) { cout << -1 << " \n"[j == m - 1]; }
        }
        return;
    }

    int half = k / 2;
    vector<vector<int>> dp_prev(n, vector<int>(m, 0));
    vector<vector<int>> dp_cur(n, vector<int>(m));

    for (int step = 1; step <= half; step++) {
        For(i, n) For(j, m) dp_cur[i][j] = inf;

        For(i, n) For(j, m) {
            if (i > 0)
                dp_cur[i][j] = min(dp_cur[i][j], dp_prev[i - 1][j] + ver[i - 1][j]);
            if (i < n - 1)
                dp_cur[i][j] = min(dp_cur[i][j], dp_prev[i + 1][j] + ver[i][j]);
            if (j > 0)
                dp_cur[i][j] = min(dp_cur[i][j], dp_prev[i][j - 1] + hor[i][j - 1]);
            if (j < m - 1)
                dp_cur[i][j] = min(dp_cur[i][j], dp_prev[i][j + 1] + hor[i][j]);
        }

        swap(dp_prev, dp_cur);
    }
    For(i, n) {
        For(j, m) { cout << 2 * dp_prev[i][j] << " \n"[j == m - 1]; }
    }
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
