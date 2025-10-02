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
    int n, k;
    rd(n, k);
    int u = n - 1;
    if (n == 4 && k == n - 1) {
        prt(-1);
        return;
    }

    auto rev = [&](int x) -> int { return x ^ u; };

    vector<pii> ans;
    vector<int> used(n, 0);

    if (k == 0) {
        for (int i = 0; i < n; i++) {
            if (used[i]) {
                continue;
            }
            ans.emplace_back(i, rev(i));
            used[i] = 1;
            used[rev(i)] = 1;
        }
    } else if (k == u) {
        ans.emplace_back(u, u - 1);
        ans.emplace_back(1, 3);
        ans.emplace_back(0, u - 3);
        used[u] = used[u - 1] = used[1] = used[3] = used[0] = used[u - 3] = 1;
        for (int i = 0; i < n; i++) {
            if (used[i]) {
                continue;
            }
            ans.emplace_back(i, rev(i));
            used[i] = 1;
            used[rev(i)] = 1;
        }
    } else {
        ans.emplace_back(u, k);
        ans.emplace_back(0, rev(k));
        used[u] = used[k] = used[0] = used[rev(k)] = 1;
        for (int i = 0; i < n; i++) {
            if (used[i]) {
                continue;
            }
            ans.emplace_back(i, rev(i));
            used[i] = 1;
            used[rev(i)] = 1;
        }
    }

    for (auto &p: ans)
        prt(p.first, p.second);
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
