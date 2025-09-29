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

int Multitest = 0;

void init() {}

void solve() {
    // int lo = 3;

    // auto f = [&](int a, int b) -> int {
    //     int ans = a;
    //     b++;
    //     while (a < b) {
    //         int mid = a + (b - a) / 2;

    //         prt_endl("?", 1, mid);
    //         int t;
    //         rd(t);

    //         if (t == -1) {
    //             b = mid;
    //         } else {
    //             ans = mid;
    //             a = max(mid, t) + 1;
    //         }
    //     }
    //     return ans;
    // };

    // int mx = 3;
    // int hi = 1;
    // while (true) {
    //     hi *= 10;
    //     prt_endl("?", 1, (1 + hi) / 2);

    //     int t;
    //     rd(t);

    //     if (t == -1) {
    //         prt_endl("!", f(mx, hi));
    //         break;
    //     } else {
    //         mx = max({mx, t, hi / 10});
    //     }
    // }

    for (int i = 2; i <= 26; i++) {
        prt_endl("?", 1, i);
        int t;
        rd(t);

        if (t == -1) {
            prt_endl("!", i - 1);
            return;
        }

        prt_endl("?", i, 1);
        int t2;
        rd(t2);
        if (t != t2) {
            prt_endl("!", t + t2);
            return;
        }
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
