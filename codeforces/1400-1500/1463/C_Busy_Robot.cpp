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

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);

    vector<pii> commands(n);
    For(i, n) {
        int a, b;
        rd(a, b);
        commands[i] = {a, b};
    }

    int ans = 0;
    int cur = 0;
    int target = commands[0].second;
    int pre_t = commands[0].first;

    for (int i = 1; i < n; i++) {
        auto [t, x] = commands[i];

        int dt = t - pre_t;
        int n_pos;
        if (target > cur) {
            n_pos = min(target, cur + dt);
        } else {
            n_pos = max(target, cur - dt);
        }

        // if (n == 3 && commands[0].second == 5 && commands[2].second == 4)
        //     debug("ans", ans);

        // if (n == 6) {
        //     debug("i", i, "ans", ans, "cur", cur, "n_pos", n_pos, "target", target);
        // }

        if (n_pos == target) {
            int pre_x = commands[i - 1].second;
            if (pre_x >= min(n_pos, cur) && pre_x <= max(n_pos, cur)) {
                ans++;
            }
            target = x;
            // if (n == 3 && commands[0].second == 5 && commands[2].second == 4)
            //     debug("i", i, "n_pos", n_pos);
        } else {
            int pre_x = commands[i - 1].second;
            if (pre_x >= min(n_pos, cur) && pre_x <= max(n_pos, cur)) {
                ans++;
            }
            // if (n == 3 && commands[0].second == 5 && commands[2].second == 4)
            //     debug("i", i, "pre_x", pre_x, "cur", cur, "n_pos", n_pos);
        }
        cur = n_pos;
        pre_t = t;
    }

    if (commands[n - 1].second >= min(target, cur) && commands[n - 1].second <= max(target, cur)) {
        ans++;
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
