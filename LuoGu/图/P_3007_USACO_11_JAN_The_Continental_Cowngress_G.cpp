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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;
constexpr long long iinf = 0x3f3f3f3f / 2;

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

#define int ll

int Multitest = 0;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    vvi g(2 * n + 1);

    F(i, 1, m) {
        int j, k;
        char a, b;
        rd(j, a, k, b);

        int f1 = (a == 'Y');
        int f2 = (b == 'Y');

        g[j + f1 * n].pb(k + !f2 * n);
        g[k + f2 * n].pb(j + !f1 * n);
    }


    int timestamp = 0;
    vector<int> dfn(2 * n + 1), low(2 * n + 1), in_stack(2 * n + 1), comp(2 * n + 1);
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

    F(i, 1, 2 * n) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    F(i, 1, n) {
        if (comp[i] == comp[i + n]) {
            prt("IMPOSSIBLE");
            return;
        }
    }

    vector<bool> visited;
    auto dfs_check = [&](this auto &&self, int u, int target) -> bool {
        if (u == target)
            return true;
        visited[u] = true;
        for (int v: g[u]) {
            if (!visited[v]) {
                if (self(v, target))
                    return true;
            }
        }
        return false;
    };

    auto can_reach = [&](int start, int target) -> bool {
        visited.assign(2 * n + 1, false);
        return dfs_check( start, target);
    };

    string s = "";
    F(i, 1, n) {
        bool f_implies_p = can_reach(i + n, i);
        bool p_implies_f = can_reach(i, i + n);

        if (f_implies_p) {
            s += 'Y';
        }
        else if (p_implies_f) {
            s += 'N';
        }
        else {
            s += '?';
        }
    }
    prt(s);
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
