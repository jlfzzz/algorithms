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

    auto ask = [&](int a, int b, int c) -> int {
        cout << "? " << a << ' ' << b << ' ' << c << endl;
        int res;
        cin >> res;
        return res;
    };

    int pre = -1;
    int x, y;
    for (int i = 1; i + 2 <= n; i++) {
        int a = i, b = i + 1, c = i + 2;
        int t = ask(a, b, c);
        if (pre == -1) {
            pre = t;
        } else {
            if (t != pre) {
                x = a, y = b;
                break;
            }
        }
    }

    vector<int> ans;
    int good, bad;
    for (int i = 1; i <= n; i++) {
        if (i == x || i == y) {
            continue;
        }

        int t = ask(i, x, y);
        if (t == 0) {
            ans.push_back(i);
            bad = i;
        } else {
            good = i;
        }
    }

    int t = ask(good, bad, x);
    if (t == 0) {
        ans.push_back(x);
    }
    t = ask(good, bad, y);
    if (t == 0) {
        ans.push_back(y);
    }

    cout << "! " << ans.size();
    for (auto &v: ans)
        cout << ' ' << v;
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
