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
    int k;
    rd(k);

    string s;
    rd(s);

    int step = 1 << (k - 1);
    int q;
    rd(q);

    int n = s.size();
    vector<int> cnt(n);
    for (int i = 0; i < step; i++) {
        if (s[i] == '?') {
            cnt[i] = 2;
        } else {
            cnt[i] = 1;
        }
    }
    for (int i = 0; i < n - 1; i += 2) {
        char fa = s[i / 2 + step];
        int j = i / 2 + step;
        if (fa == '?') {
            cnt[j] = cnt[i] + cnt[i + 1];
        } else if (fa == '1') {
            cnt[j] = cnt[i + 1];
        } else {
            cnt[j] = cnt[i];
        }
    }


    while (q--) {
        int p;
        char c;
        rd(p, c);
        p--;

        s[p] = c;

        if (p < step) {
            if (c == '?') {
                cnt[p] = 2;
            } else {
                cnt[p] = 1;
            }
        } else {
            int son = (p - step) * 2;
            if (c == '?') {
                cnt[p] = cnt[son] + cnt[son + 1];
            } else if (c == '0') {
                cnt[p] = cnt[son];
            } else {
                cnt[p] = cnt[son + 1];
            }
        }

        if (p & 1) {
            p--;
        }

        while (p < n - 1) {
            int fa = p / 2 + step;
            char cfa = s[fa];
            if (cfa == '?') {
                cnt[fa] = cnt[2 * (fa - step)] + cnt[2 * (fa - step) + 1];
            } else if (cfa == '0') {
                cnt[fa] = cnt[2 * (fa - step)];
            } else {
                cnt[fa] = cnt[2 * (fa - step) + 1];
            }
            p = fa;
        }

        prt(cnt[n - 1]);
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
