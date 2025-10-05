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
    int n;
    rd(n);

    auto ask = [&](int u) -> vector<int> {
        cout << "? " << u << endl;
        vector<int> res(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> res[i];
        }
        return res;
    };

    vector<int> d1 = ask(1);
    vector<int> even, odd;
    for (int i = 1; i <= n; i++) {
        if (d1[i] % 2 == 0)
            even.push_back(i);
        else
            odd.push_back(i);
    }

    bool f = (even.size() <= odd.size());
    vector<pii> ans;

    if (f) {
        for (int v = 1; v <= n; v++)
            if (d1[v] == 1)
                ans.emplace_back(1, v);
        for (int u: even)
            if (u != 1) {
                auto d = ask(u);
                for (int v = 1; v <= n; v++)
                    if (d[v] == 1)
                        ans.emplace_back(u, v);
            }
    } else {
        for (int u: odd) {
            auto d = ask(u);
            for (int v = 1; v <= n; v++)
                if (d[v] == 1)
                    ans.emplace_back(u, v);
        }
    }

    cout << "!" << '\n';
    for (auto &[a, b]: ans)
        cout << a << ' ' << b << '\n';
    cout << endl;
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
