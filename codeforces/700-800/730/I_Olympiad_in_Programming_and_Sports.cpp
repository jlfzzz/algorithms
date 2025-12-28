#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define pob pop_back
#define ep emplace
#define ins insert
#define all(x) (x).begin(), (x).end()
#define all2(x, i) (x).begin() + (i), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
#define us unsigned
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
constexpr int MOD2 = int(1e9 + 7);
constexpr int MOD = int(998244353);
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

void init() {}

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

struct S {
    int id;
    ll a, b;
};

void solve3() {
    int n, p, s;
    rd(n, p, s);

    vector<S> v(n + 1);
    F(i, 1, n) v[i].id = i;
    F(i, 1, n) rd(v[i].a);
    F(i, 1, n) rd(v[i].b);

    int S_node = 0;
    int P_node = n + 1;
    int Sport_node = n + 2;
    int T_node = n + 3;

    MCMF mcf(n + 4);

    F(i, 1, n) { mcf.addEdge(S_node, i, 1, 0); }

    F(i, 1, n) {
        mcf.addEdge(i, P_node, 1, -v[i].a);
        mcf.addEdge(i, Sport_node, 1, -v[i].b);
    }

    mcf.addEdge(P_node, T_node, p, 0);
    mcf.addEdge(Sport_node, T_node, s, 0);

    auto [max_flow, min_cost] = mcf.minCostMaxFlow(S_node, T_node);

    prt(-min_cost);

    vi ans1, ans2;

    F(i, 1, n) {
        for (auto &e: mcf.g[i]) {
            if (e.cap == 0) {
                if (e.to == P_node) {
                    ans1.pb(v[i].id);
                } else if (e.to == Sport_node) {
                    ans2.pb(v[i].id);
                }
            }
        }
    }

    prv(ans1);
    prv(ans2);
}

void solve() {
    int n, p, s;
    rd(n, p, s);

    vector<S> v(n + 1);
    F(i, 1, n) v[i].id = i;
    F(i, 1, n) rd(v[i].a);
    F(i, 1, n) rd(v[i].b);

    sort(all2(v, 1), [](const S &x, const S &y) { return x.a > y.a; });

    prq<pii> pq1, pq2, pq3;

    ll ans = 0;
    vi st(n + 1, 0);

    F(i, 1, p) {
        ans += v[i].a;
        st[i] = 1;
        pq1.emplace(v[i].b - v[i].a, i);
    }

    F(i, p + 1, n) {
        st[i] = 0;
        pq2.emplace(v[i].a, i);
        pq3.emplace(v[i].b, i);
    }

    F(k, 1, s) {
        while (!pq2.empty() && st[pq2.top().se] != 0)
            pq2.pop();
        while (!pq3.empty() && st[pq3.top().se] != 0)
            pq3.pop();
        while (!pq1.empty() && st[pq1.top().se] != 1)
            pq1.pop();

        ll val1 = -INF;
        if (!pq3.empty())
            val1 = pq3.top().fi;

        ll val2 = -INF;
        if (!pq1.empty() && !pq2.empty()) {
            val2 = pq1.top().fi + pq2.top().fi;
        }

        if (val1 > val2) {
            auto [val, id] = pq3.top();
            pq3.pop();
            ans += val;
            st[id] = 2;
        } else {
            auto [diff, id1] = pq1.top();
            pq1.pop();
            auto [v1, id2] = pq2.top();
            pq2.pop();

            ans += diff + v1;

            st[id1] = 2;
            st[id2] = 1;

            pq1.emplace(v[id2].b - v[id2].a, id2);
        }
    }

    prt(ans);

    vi ans1, ans2;
    F(i, 1, n) {
        if (st[i] == 1)
            ans1.pb(v[i].id);
        else if (st[i] == 2)
            ans2.pb(v[i].id);
    }

    prv(ans1);
    prv(ans2);
}

void solve2() {
    int n, p, s;
    rd(n, p, s);

    vector<S> v(n + 1);
    F(i, 1, n) v[i].id = i;
    F(i, 1, n) rd(v[i].a);
    F(i, 1, n) rd(v[i].b);

    sort(all2(v, 1), [](const S &x, const S &y) { return x.a > y.a; });

    vvl dp(n + 1, vl(s + 1, -INF));
    vvi path(n + 1, vi(s + 1, 0));

    dp[0][0] = 0;

    F(i, 1, n) {
        F(j, 0, s) {
            if (dp[i - 1][j] != -INF) {
                ll val = dp[i - 1][j];
                int type = 0;

                int cnt = (i - 1) - j;

                if (cnt < p) {
                    val += v[i].a;
                    type = 2;
                }

                if (val > dp[i][j]) {
                    dp[i][j] = val;
                    path[i][j] = type;
                }
            }

            if (j > 0 && dp[i - 1][j - 1] != -INF) {
                ll val = dp[i - 1][j - 1] + v[i].b;
                if (val > dp[i][j]) {
                    dp[i][j] = val;
                    path[i][j] = 1;
                }
            }
        }
    }

    prt(dp[n][s]);

    vi ans1, ans2;
    int cur = s;

    D(i, n, 1) {
        int t = path[i][cur];
        if (t == 1) {
            ans2.pb(v[i].id);
            cur--;
        } else if (t == 2) {
            ans1.pb(v[i].id);
        }
    }

    prv(ans1);
    prv(ans2);
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
        solve3();
    }
}
