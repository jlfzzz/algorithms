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

    vector<vector<int>> g(n + 1);
    vector<int> deg(n + 1);
    For(i, n) {
        int k;
        rd(k);
        For(j, k) {
            int t;
            rd(t);
            g[t].push_back(i + 1);
            deg[i + 1]++;
        }
    }

    set<int> cur;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            cur.insert(i);
        }
    }

    int round = 1;
    vector<int> vis(n + 1);
    for (;; round++) {
        set<int> nxt;
        auto it = cur.begin();
        while (it != cur.end()) {
            int now = *it;
            vis[now] = 1;
            for (int v: g[now]) {
                deg[v]--;
                if (deg[v] == 0) {
                    if (v < now) {
                        nxt.insert(v);
                    } else {
                        cur.insert(v);
                    }
                }
            }
            it++;
        }

        cur.swap(nxt);
        if (cur.empty()) {
            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            prt(-1);
            return;
        }
    }

    prt(round);
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
