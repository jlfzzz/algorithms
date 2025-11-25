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

#ifdef WOAIHUTAO
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 0;

using ll = long long;
using Flow = long long;

struct Edge {
    int to, rev;
    Flow cap;
    Flow original_cap;
};

// Dinic 最大流 + 最小割
struct Dinic {
    int n;
    vector<vector<Edge>> g;
    vector<int> level;
    vector<int> it;
    Dinic(int n = 0) { init(n + 5); }

    void init(int _n) {
        n = _n;
        g.assign(n, {});
        level.assign(n, -1);
        it.assign(n, 0);
    }

    void add(int u, int v, Flow c) {
        g[u].emplace_back(Edge{v, (int) g[v].size(), c, c}); // 保存原始容量
        g[v].emplace_back(Edge{u, (int) g[u].size() - 1, 0, 0});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge &e: g[u]) {
                if (level[e.to] < 0 && e.cap > 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    Flow dfs(int u, int t, Flow f) {
        if (u == t)
            return f;
        for (int &i = it[u]; i < (int) g[u].size(); ++i) {
            Edge &e = g[u][i];
            if (e.cap > 0 && level[e.to] == level[u] + 1) {
                Flow pushed = dfs(e.to, t, min(f, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    Flow maxFlow(int s, int t) {
        Flow flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (true) {
                Flow pushed = dfs(s, t, numeric_limits<Flow>::max());
                if (pushed == 0)
                    break;
                flow += pushed;
            }
        }
        return flow;
    }

    vector<int> minCut(int s) {
        vector<int> vis(n);
        queue<int> q;
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &e: g[u]) {
                if (e.cap > 0 && !vis[e.to]) {
                    vis[e.to] = 1;
                    q.push(e.to);
                }
            }
        }
        return vis;
    }

    Flow minCutEdges(int s, int t) {
        vector<vector<Flow>> backup_cap(n);
        for (int i = 0; i < n; i++) {
            backup_cap[i].resize(g[i].size());
            for (int j = 0; j < g[i].size(); j++) {
                backup_cap[i][j] = g[i][j].cap;
            }
        }

        for (int i = 0; i < n; i++) {
            for (auto &e: g[i]) {
                if (e.original_cap > 0) {
                    e.cap = 1;
                } else {
                    e.cap = 0;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                Edge &e = g[i][j];
                if (e.original_cap > 0) {
                    Edge &rev = g[e.to][e.rev];
                    rev.cap = 0;
                }
            }
        }

        Flow result = maxFlow(s, t);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < g[i].size(); j++) {
                g[i][j].cap = backup_cap[i][j];
            }
        }

        return result;
    }
};

void init() {}

void solve() {
    int n;
    rd(n);
    vector<db> sx(n), sy(n), gx(n), gy(n);
    F(i, 0, n - 1) { rd(sx[i], sy[i]); }
    F(i, 0, n - 1) { rd(gx[i], gy[i]); }

    vector<vector<db>> dist(n, vector<db>(n));
    db hi = 0;
    F(i, 0, n - 1) {
        F(j, 0, n - 1) {
            db dx = sx[i] - gx[j];
            db dy = sy[i] - gy[j];
            dist[i][j] = sqrtl(dx * dx + dy * dy);
            if (dist[i][j] > hi) {
                hi = dist[i][j];
            }
        }
    }
    db lo = 0;

    auto can = [&](db t) -> bool {
        int S = 0;
        int L = 1;
        int R = L + n;
        int T = R + n;
        int V = T + 1;
        Dinic mf(V);
        mf.init(V);
        F(i, 0, n - 1) { mf.add(S, L + i, 1); }
        F(j, 0, n - 1) { mf.add(R + j, T, 1); }
        F(i, 0, n - 1) {
            F(j, 0, n - 1) {
                if (dist[i][j] <= t + (db) 1e-12) {
                    mf.add(L + i, R + j, 1);
                }
            }
        }
        Flow f = mf.maxFlow(S, T);
        return f == n;
    };

    F(it, 0, 80) {
        db mid = (lo + hi) / 2;
        if (can(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    cout.setf(ios::fixed);
    cout << setprecision(15) << (long double) hi << '\n';
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
