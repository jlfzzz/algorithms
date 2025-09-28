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
    void read(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void read(T &x, Args &...args) {
        cin >> x;
        read(args...);
    }

    template<typename A, typename B>
    void read(pair<A, B> &p) {
        cin >> p.first >> p.second;
    }

    template<typename T>
    void read_vec(vector<T> &v) {
        for (auto &x: v) {
            read(x);
        }
    }

    template<typename T>
    void read_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            read(v[i]);
        }
    }
} // namespace io

using namespace io;

int Multitest = 0;

void init() {}

void solve() {
    int n, k;
    read(n, k);

    if (n == 1) {
        if (k != 2 * n) {
            prt(-1);
        } else {
            prt(n);
        }
        return;
    }

    if (n == 2) {
        if (k != 2 * n + n - 1) {
            prt(-1);
        } else {
            prt(n, n - 1);
        }
        return;
    }

    int t = k - n - n - n + 1;
    if (t < 0) {
        prt(-1);
        return;
    }

    vector<int> chosen(n + 1);
    for (int x = n - 2; x >= 1; x--) {
        if (x <= t) {
            chosen[x] = 1;
            t -= x;
        }
    }

    if (t) {
        prt(-1);
        return;
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (chosen[i]) {
            ans.push_back(i);
        }
    }
    ans.push_back(n - 1);
    for (int i = 1; i <= n - 2; i++) {
        if (!chosen[i]) {
            ans.push_back(i);
        }
    }
    ans.push_back(n);
    prt_vec(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        read(T);
    }
    while (T--)
        solve();
    return 0;
}
