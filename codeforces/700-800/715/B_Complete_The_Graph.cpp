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

int Multitest = 0;

void init() {}

void solve() {
    int n, m, l, s, t;
    rd(n, m, l, s, t);

    struct Edge {
        int v, id;
        ll w;
    };
    vector<vector<Edge>> g(n + 1);
    struct InEdge {
        int u, v;
        ll w;
    };
    vector<InEdge> edges(m + 1);
    vector<ll> assigned(m + 1, -1);
    F(i, 1, m) {
        int u, v;
        ll w;
        rd(u, v, w);
        g[u].pb(v, i, w);
        g[v].pb(u, i, w);
        edges[i] = {u, v, w};
    }

    vector<ll> dis(n + 1, INF);
    prq<pii, vp, greater<>> pq;
    pq.emplace(0, s);
    dis[s] = 0;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dis[u]) {
            continue;
        }

        for (auto [v, id, w]: g[u]) {
            if (w == 0) {
                continue;
            }

            ll nd = d + w;
            if (nd < dis[v]) {
                dis[v] = nd;
                pq.emplace(nd, v);
            }
        }
    }

    if (dis[t] < l) {
        prt("NO");
        return;
    }

    vector<ll> dis2(n + 1, INF);
    prq<pii, vp, greater<>> pq2;
    pq2.emplace(0, s);
    dis2[s] = 0;
    while (!pq2.empty()) {
        auto [d, u] = pq2.top();
        pq2.pop();

        if (d > dis2[u]) {
            continue;
        }

        for (auto [v, id, w]: g[u]) {
            if (w == 0) {
                w = 1;
            }

            ll nd = d + w;
            if (nd < dis2[v]) {
                dis2[v] = nd;
                pq2.emplace(nd, v);
            }
        }
    }

    if (dis2[t] > l) {
        prt("NO");
        return;
    }

    if (dis2[t] == l) {
        prt("YES");
        F(i, 1, m) {
            if (edges[i].w == 0) {
                prt(edges[i].u, edges[i].v, 1LL);
            } else {
                prt(edges[i].u, edges[i].v, edges[i].w);
            }
        }
        return;
    }

    vector<ll> distT(n + 1, INF);
    prq<pii, vp, greater<>> pqT;
    pqT.emplace(0, t);
    distT[t] = 0;
    while (!pqT.empty()) {
        auto [d, u] = pqT.top();
        pqT.pop();
        if (d > distT[u])
            continue;
        for (auto [v, id, w]: g[u]) {
            ll ww = (w == 0 ? 1 : w);
            ll nd = d + ww;
            if (nd < distT[v]) {
                distT[v] = nd;
                pqT.emplace(nd, v);
            }
        }
    }

    struct Ans {
        int u, v;
        ll w;
    };
    vector<Ans> ans(m + 1);

    vector<ll> dis3(n + 1, INF);
    prq<pii, vp, greater<>> pq3;
    pq3.emplace(0, s);
    dis3[s] = 0;
    while (!pq3.empty()) {
        auto [d, u] = pq3.top();
        pq3.pop();

        if (d > dis3[u]) {
            continue;
        }

        for (auto [v, id, w]: g[u]) {
            ll ww = w;
            if (ww == 0) {
                if (assigned[id] == -1) {
                    ll need = (ll) l - d - distT[v];
                    if (need < 1)
                        need = 1;
                    assigned[id] = need;
                    ans[id] = {static_cast<int>(u), v, need};
                }
                ww = assigned[id];
            }

            ll nd = d + ww;
            if (nd < dis3[v]) {
                dis3[v] = nd;
                pq3.emplace(nd, v);
            }
        }
    }

    if (dis3[t] != l) {
        prt("NO");
        return;
    }

    prt("YES");
    F(i, 1, m) {
        if (edges[i].w == 0) {
            ll outw = (assigned[i] != -1 ? assigned[i] : (ll) 1e18);
            prt(edges[i].u, edges[i].v, outw);
        } else {
            prt(edges[i].u, edges[i].v, edges[i].w);
        }
    }
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
