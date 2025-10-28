#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

namespace utils {
    void dbg() { cerr << "\n"; }

    template<typename T, typename... Args>
    void dbg(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        dbg(args...);
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
    void prv(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prv(const vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
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
    void rv(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rv(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }
} // namespace utils

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n, m;
    rd(n, m);
    vp segs(m + 1);
    F(i, 1, m) {
        rd(segs[i].fi, segs[i].se);
        if (segs[i].se < segs[i].fi) {
            swap(segs[i].se, segs[i].fi);
        }
    }

    vvi g(2 * m + 1);
    F(i, 1, m) {
        auto [x1, y1] = segs[i];
        F(j, 1, m) {
            if (i == j) {
                continue;
            }

            auto [x2, y2] = segs[j];
            if ((x1 < x2 && x2 < y1 && y1 < y2) || (x2 < x1 && x1 < y2 && y2 < y1)) {
                g[i].pb(j + m);
                g[i + m].pb(j);
            }
        }
    }

    int timestamp = 0;
    vector<int> dfn(2 * m + 1), low(2 * m + 1), in_stack(2 * m + 1), comp(2 * m + 1);
    vector<vector<int>> comps;
    stack<int> stk;

    auto tarjan = [&](this auto &&tarjan, int u) -> void {
        dfn[u] = low[u] = ++timestamp;
        stk.push(u);
        in_stack[u] = true;

        for (int v: g[u]) {
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            vector<int> scc;
            while (true) {
                int x = stk.top();
                stk.pop();
                in_stack[x] = false;
                comp[x] = comps.size() + 1;
                scc.push_back(x);
                if (x == u)
                    break;
            }
            comps.emplace_back(scc);
        }
    };

    F(i, 1, 2 * m) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    F(i, 1, m) {
        if (comp[i] == comp[i + m]) {
            prt("Impossible");
            return;
        }
    }

    F(i, 1, m) {
        if (comp[i] > comp[i + m]) {
            cout << "i";
        } else {
            cout << "o";
        }
    }
    cout << endl;
}

int main() {
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
