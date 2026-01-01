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

void solve() {
    int n, m;
    rd(n, m);

    vvp g(n + 1);
    struct RawEdge {
        int u, v;
        ll w;
    };
    vector<RawEdge> edges(m + 1);

    F(i, 1, m) {
        ll a, b, c;
        rd(a, b, c);
        g[a].pb(b, c);
        g[b].pb(a, c);
        edges[i] = {(int) a, (int) b, c};
    }

    auto dij = [&](int start) -> vl {
        vl dis(n + 1, INF);
        dis[start] = 0;
        prq<pii, vp, greater<>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dis[u])
                continue;
            for (auto [v, w]: g[u]) {
                if (d + w < dis[v]) {
                    dis[v] = d + w;
                    pq.emplace(d + w, v);
                }
            }
        }
        return dis;
    };

    auto dis1 = dij(1);
    auto dis2 = dij(n);

    ll D = dis1[n];

    struct E {
        int to, id;
    };
    vector<vector<E>> sps_g(n + 1);

    F(i, 1, m) {
        auto [u, v, w] = edges[i];
        bool on_path = false;
        if (dis1[u] + w + dis2[v] == D)
            on_path = true;
        if (dis1[v] + w + dis2[u] == D)
            on_path = true;

        if (on_path) {
            sps_g[u].push_back({v, i});
            sps_g[v].push_back({u, i});
        }
    }

    vector<int> dfn(n + 1, 0), low(n + 1, 0);
    int ts = 0;
    vector<bool> is_bridge(m + 1, false);

    auto tarjan = [&](auto &&self, int u, int in_edge_id) -> void {
        dfn[u] = low[u] = ++ts;
        for (auto &e: sps_g[u]) {
            int v = e.to;
            int id = e.id;
            if (id == in_edge_id)
                continue;

            if (!dfn[v]) {
                self(self, v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] > dfn[u]) {
                    is_bridge[id] = true;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };

    if (sps_g[1].size() > 0 || n == 1) {
        tarjan(tarjan, 1, -1);
    }

    F(i, 1, m) {
        if (is_bridge[i])
            prt("Yes");
        else
            prt("No");
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
