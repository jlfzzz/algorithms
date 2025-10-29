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
constexpr int MOD = int(1e9 + 7);
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

void solve() {
    int n, q;
    rd(n, q);

    vvl mat(n + 1, vl(n + 1));
    F(i, 1, n) {
        F(j, 1, n) { rd(mat[i][j]); }
    }

    vvl pre0(n + 1, vl(n + 1)), pre1(n + 1, vl(n + 1));
    vvl prei(n + 1, vl(n + 1)), prej(n + 1, vl(n + 1));

    F(i, 1, n) {
        F(j, 1, n) {
            pre0[i][j] = mat[i][j] + pre0[i - 1][j] + pre0[i][j - 1] - pre0[i - 1][j - 1];
            pre1[i][j] = mat[i][j] * ((i - 1) * n + j) + pre1[i - 1][j] + pre1[i][j - 1] - pre1[i - 1][j - 1];
            prei[i][j] = mat[i][j] * i + prei[i - 1][j] + prei[i][j - 1] - prei[i - 1][j - 1];
            prej[i][j] = mat[i][j] * j + prej[i - 1][j] + prej[i][j - 1] - prej[i - 1][j - 1];
        }
    }

    vl ans;
    while (q--) {
        ll x1, y1, x2, y2;
        rd(x1, y1, x2, y2);

        ll sum0 = pre0[x2][y2] - pre0[x2][y1 - 1] - pre0[x1 - 1][y2] + pre0[x1 - 1][y1 - 1];
        ll sumI = prei[x2][y2] - prei[x2][y1 - 1] - prei[x1 - 1][y2] + prei[x1 - 1][y1 - 1];
        ll sumJ = prej[x2][y2] - prej[x2][y1 - 1] - prej[x1 - 1][y2] + prej[x1 - 1][y1 - 1];
        ll w = y2 - y1 + 1;
        ll sum1 = sumJ + w * sumI + sum0 * (1 - y1 - w * x1);
        ans.pb(sum1);
    }
    prv(ans);
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
