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
    int n, q;
    rd(n, q);

    vector<int> a(n + 1);
    rd_vec(a, 1);

    vector<int> b;
    b.push_back(0);
    for (int i = 1; i <= n; i++)
        if (a[i] != 0)
            b.push_back(i);
    int m = b.size() - 1;

    vector<int> pre1(m + 1), pre2(m + 1);
    for (int i = 1; i <= m; i++) {
        pre1[i] = pre1[i - 1] + a[b[i]];
        pre2[i] = pre2[i - 1] ^ a[b[i]];
    }

    auto calc = [&](int l, int r) -> int { return pre1[r] - pre1[l - 1] - (pre2[r] ^ pre2[l - 1]); };

    while (q--) {
        int L, R;
        rd(L, R);

        if (m == 0) {
            prt(L, L);
            continue;
        }

        int l = int(lower_bound(b.begin() + 1, b.end(), L) - b.begin());
        int r = int(upper_bound(b.begin() + 1, b.end(), R) - b.begin()) - 1;

        if (l > r) {
            prt(L, L);
            continue;
        }

        int ansl = l, ansr = r;
        int limL = min(l + 30, r);
        int limR = max(r - 30, l);
        for (int i = l; i <= limL; i++) {
            for (int j = r; j >= max(limR, i); j--) {
                if (calc(i, j) == calc(l, r)) {
                    if (b[j] - b[i] < b[ansr] - b[ansl]) {
                        ansl = i;
                        ansr = j;
                    }
                }
            }
        }

        prt(b[ansl], b[ansr]);
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
