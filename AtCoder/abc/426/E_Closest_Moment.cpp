#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
[[maybe_unused]] constexpr int MOD = int(1e9 + 7);
[[maybe_unused]] constexpr int MOD2 = int(998244353);
[[maybe_unused]] constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

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
    int tsx, tsy, tgx, tgy;
    int asx, asy, agx, agy;
    rd(tsx, tsy, tgx, tgy, asx, asy, agx, agy);

    double d1x = (double) tgx - (double) tsx, d1y = (double) tgy - (double) tsy;
    double d2x = (double) agx - (double) asx, d2y = (double) agy - (double) asy;
    double T1 = hypot(d1x, d1y);
    double T2 = hypot(d2x, d2y);

    double v1x = d1x / T1, v1y = d1y / T1;
    double v2x = d2x / T2, v2y = d2y / T2;

    auto dist2 = [&](double t) -> double {
        double x1 = t <= T1 ? ((double) tsx + v1x * t) : (double) tgx;
        double y1 = t <= T1 ? ((double) tsy + v1y * t) : (double) tgy;
        double x2 = t <= T2 ? ((double) asx + v2x * t) : (double) agx;
        double y2 = t <= T2 ? ((double) asy + v2y * t) : (double) agy;
        double dx = x1 - x2, dy = y1 - y2;
        return dx * dx + dy * dy;
    };

    auto calc = [&](double L, double R) -> double {
        if (R - L <= 0)
            return dist2(L);
        for (int i = 0; i < 80; i++) {
            double m1 = (2.0 * L + R) / 3.0;
            double m2 = (L + 2.0 * R) / 3.0;
            if (dist2(m1) > dist2(m2))
                L = m1;
            else
                R = m2;
        }
        return dist2((L + R) / 2.0);
    };

    double L = 0.0, M = min(T1, T2), R = max(T1, T2);
    double ans2 = min({dist2(L), dist2(M), dist2(R)});
    ans2 = min(ans2, calc(L, M));
    if (M < R)
        ans2 = min(ans2, calc(M, R));

    double ans = sqrt(ans2);
    cout.setf(std::ios::fixed);
    cout << setprecision(15) << ans << '\n';
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
