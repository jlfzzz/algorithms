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
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
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

int Multitest = 1;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    vp edges(m + 1);
    F(i, 1, m) {
        rd(edges[i].fi, edges[i].se);
        if (edges[i].fi > edges[i].se) {
            swap(edges[i].fi, edges[i].se);
        }
    }

    map<int, int> id;
    F(i, 1, n) {
        int t;
        rd(t);
        id[t] = i;
    }

    if (m > 5 * n) {
        prt("NO");
        return;
    }

    // 将非环边映射为环上的弦 (a,b)，a<b，且去除环边
    vp chords;
    chords.reserve(m);
    F(i, 1, m) {
        int u = edges[i].fi, v = edges[i].se;
        int a = id[u], b = id[v];
        if (a > b)
            swap(a, b);
        // 跳过环边：相邻或 (1,n)
        if (b - a == 1 || (a == 1 && b == n))
            continue;
        chords.pb(a, b);
    }

    int K = (int) chords.size();
    if (K == 0) {
        prt("YES");
        return;
    }

    // 2-SAT：变量为每条弦是否在某一侧，索引 1..K，取反偏移 +K
    vvi g(2 * K + 1);
    auto var = [&](int i) { return i; };
    auto neg = [&](int i) { return i + K; };

    auto cross = [&](const pii &A, const pii &B) -> bool {
        int a = (int) A.fi, b = (int) A.se;
        int c = (int) B.fi, d = (int) B.se;
        return (a < c && c < b && b < d) || (c < a && a < d && d < b);
    };

    F(i, 1, K) {
        F(j, 1, K) {
            if (i == j) {
                continue;
            }
            if (cross(chords[i - 1], chords[j - 1])) {
                g[var(i)].pb(neg(j));
                g[neg(i)].pb(var(j));
            }
        }
    }

    int timestamp = 0;
    vector<int> dfn(2 * K + 1), low(2 * K + 1), in_stack(2 * K + 1), comp(2 * K + 1);
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
            vi scc;
            while (true) {
                int x = stk.top();
                stk.pop();
                in_stack[x] = false;
                comp[x] = comps.size() + 1;
                scc.pb(x);
                if (x == u)
                    break;
            }
            comps.emplace_back(scc);
        }
    };

    F(i, 1, 2 * K) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    F(i, 1, K) {
        if (comp[i] == comp[i + K]) {
            prt("NO");
            return;
        }
    }

    prt("YES");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--) {
        solve();
    }
}
