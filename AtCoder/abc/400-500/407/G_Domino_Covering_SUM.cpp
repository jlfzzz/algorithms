#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define vi vector<int>
#define vp vector<pii>
#define vl vector<long long>
#define vvi vector<vector<int>>
#define vvp vector<vector<pii>>
#define vvl vector<vector<long long>>
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

namespace utils {
    template<typename A, typename B>
    ostream &operator<<(ostream &os, const pair<A, B> &p) {
        return os << '(' << p.first << ", " << p.second << ')';
    }

    template<typename Tuple, size_t... Is>
    void print_tuple(ostream &os, const Tuple &t, index_sequence<Is...>) {
        ((os << (Is == 0 ? "" : ", ") << get<Is>(t)), ...);
    }

    template<typename... Args>
    ostream &operator<<(ostream &os, const tuple<Args...> &t) {
        os << '(';
        print_tuple(os, t, index_sequence_for<Args...>{});
        return os << ')';
    }

    template<typename T, typename = decltype(begin(declval<T>())), typename = enable_if_t<!is_same_v<T, string>>>
    ostream &operator<<(ostream &os, const T &v) {
        os << '{';
        bool first = true;
        for (auto &x: v) {
            if (!first)
                os << ", ";
            first = false;
            os << x;
        }
        return os << '}';
    }

    void debug_out() { cerr << endl; }

    template<typename Head, typename... Tail>
    void debug_out(Head H, Tail... T) {
        cerr << H;
        if (sizeof...(T))
            cerr << " ";
        debug_out(T...);
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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

using ll = long long;
using Flow = long long;

struct Edge {
    int to, rev;
    Flow cap;
    ll cost;
};

struct MCMF {
    int n;
    vector<vector<Edge>> g;
    vector<ll> dis;
    vector<int> pre, pre_e;

    MCMF(int _n) : n(_n), g(_n), dis(_n), pre(_n), pre_e(_n) {}

    void addEdge(int u, int v, Flow cap, ll cost) {
        g[u].push_back({v, (int) g[v].size(), cap, cost});
        g[v].push_back({u, (int) g[u].size() - 1, 0, -cost});
    }

    bool spfa(int s, int t) {
        fill(dis.begin(), dis.end(), INF);
        vector<bool> inq(n, false);
        queue<int> q;

        dis[s] = 0;
        q.push(s);
        inq[s] = true;
        pre[s] = -1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int i = 0; i < g[u].size(); i++) {
                Edge &e = g[u][i];
                if (e.cap > 0 && dis[u] + e.cost < dis[e.to]) {
                    dis[e.to] = dis[u] + e.cost;
                    pre[e.to] = u;
                    pre_e[e.to] = i;
                    if (!inq[e.to]) {
                        q.push(e.to);
                        inq[e.to] = true;
                    }
                }
            }
        }
        return dis[t] != INF;
    }

    pair<Flow, ll> minCostMaxFlow(int s, int t) {
        Flow flow = 0;
        ll cost = 0;
        while (spfa(s, t)) {
            if (dis[t] >= 0)
                break;
            Flow f = INF;
            for (int v = t; v != s; v = pre[v]) {
                f = min(f, g[pre[v]][pre_e[v]].cap);
            }
            for (int v = t; v != s; v = pre[v]) {
                Edge &e = g[pre[v]][pre_e[v]];
                e.cap -= f;
                g[v][e.rev].cap += f;
                cost += (ll) f * e.cost;
            }
            flow += f;
        }
        return {flow, cost};
    }
};

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int h, w;
    rd(h, w);

    vvl a(h, vl(w));
    ll sum_all = 0;
    F(i, 0, h - 1) {
        F(j, 0, w - 1) {
            rd(a[i][j]);
            sum_all += a[i][j];
        }
    }

    int S = h * w;
    int T = h * w + 1;
    MCMF mcmf(h * w + 2);

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    F(i, 0, h - 1) {
        F(j, 0, w - 1) {
            if ((i + j) % 2 == 0) {
                int u = i * w + j;
                mcmf.addEdge(S, u, 1, 0);
                F(k, 0, 3) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    if (ni >= 0 && ni < h && nj >= 0 && nj < w) {
                        int v = ni * w + nj;
                        if (a[i][j] + a[ni][nj] < 0) {
                            mcmf.addEdge(u, v, 1, a[i][j] + a[ni][nj]);
                        }
                    }
                }
            } else {
                int v = i * w + j;
                mcmf.addEdge(v, T, 1, 0);
            }
        }
    }

    auto [flow, cost] = mcmf.minCostMaxFlow(S, T);
    prt(sum_all - cost);
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
