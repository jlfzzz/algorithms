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

    struct E {
        int to, id;
    };
    vector<vector<E>> g(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    vector<int> dfn(n + 1), low(n + 1);
    int ts = 0;
    struct Bridge {
        int a, b, id;
    };
    vector<Bridge> bridges;
    vector<int> sz(n + 1), blockId(n + 1);
    vector<int> hasN(n + 1, 0);
    int bid = 0;
    map<int, int> blockSz;
    auto tarjan = [&](this auto &&tarjan, int u, int pe) -> void {
        dfn[u] = low[u] = ++ts;
        blockId[u] = bid;
        sz[u] = 1;
        hasN[u] = (u == n);
        for (auto e: g[u]) {
            if (e.id == pe)
                continue;
            int v = e.to;
            if (!dfn[v]) {
                tarjan(v, e.id);
                low[u] = min(low[u], low[v]);
                sz[u] += sz[v];
                if (low[v] > dfn[u]) {
                    bridges.emplace_back(u, v, e.id);
                }
                if (hasN[v])
                    hasN[u] = 1;
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, -1);
            blockSz[bid] = sz[i];
            bid++;
        }
    }

    vp starts;
    for (auto &br: bridges) {
        if (hasN[br.b]) {
            starts.emplace_back(br.a, br.id);
            starts.emplace_back(br.b, br.id);
        }
    }

    vp ans(n + 1, {inf, inf});
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    for (auto [node, eid]: starts) {
        if (make_pair(0, eid) < ans[node]) {
            ans[node] = {0, eid};
            pq.emplace(0, eid, node);
        }
    }
    while (!pq.empty()) {
        auto [d, eid, u] = pq.top();
        pq.pop();
        if (ans[u].first != d || ans[u].second != eid)
            continue;
        for (auto e: g[u]) {
            int v = e.to;
            pii cand = {d + 1, eid};
            if (cand < ans[v]) {
                ans[v] = cand;
                pq.emplace(cand.first, cand.second, v);
            }
        }
    }

    int q;
    rd(q);
    vector<int> ANS(q);
    for (int i = 0; i < q; ++i) {
        int c;
        rd(c);
        ANS[i] = (ans[c].first < inf ? ans[c].second : -1);
    }
    prv(ANS);
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
