#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
#define pb push_back
#define pf push_front
#define eb emplace_back
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
    int n;
    rd(n);
    vector<int> a(n);
    rd_vec(a);

    int mx = ranges::max(a);
    int m = bit_width((ull) mx);
    int U = 1 << m;

    vector<array<int, 2>> pos(U, array<int, 2>{-1, -1});
    auto push = [&](array<int, 2> &p, int idx) {
        if (idx > p[0]) {
            p[1] = p[0];
            p[0] = idx;
        } else if (idx > p[1] && idx != p[0]) {
            p[1] = idx;
        }
    };

    for (int i = 0; i < n; i++)
        push(pos[a[i]], i);

    for (int bit = 0; bit < m; bit++) {
        for (int mask = 0; mask < U; mask++) {
            if ((mask >> bit & 1) == 0) {
                push(pos[mask], pos[mask | (1 << bit)][0]);
                push(pos[mask], pos[mask | (1 << bit)][1]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n - 2; i++) {
        int cur = a[i];
        int mask = 0;
        for (int bit = m - 1; bit >= 0; bit--) {
            if (cur >> bit & 1) {
                continue;
            }
            auto check = [&](int mask, int num) -> bool {
                if (pos[mask][1] > num) {
                    return true;
                }
                return false;
            };

            if (check(mask | (1 << bit), i)) {
                mask |= 1 << bit;
            }
        }

        ans = max(ans, cur | mask);
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
