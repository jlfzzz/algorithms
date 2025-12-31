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

struct Edge {
    int u, v;
    ll w;
};

struct Q {
    int op, u, v;
};

void solve() {
    int n, m, q;
    rd(n, m, q);

    vector<Edge> edges(m + 1);
    F(i, 1, m) { rd(edges[i].u, edges[i].v, edges[i].w); }

    vector<Q> qs(q + 1);
    vi is_del(m + 1, 0);

    F(i, 1, q) {
        int op;
        rd(op);
        qs[i].op = op;
        if (op == 1) {
            int idx;
            rd(idx);
            qs[i].u = idx;
            is_del[idx] = 1;
        } else {
            rd(qs[i].u, qs[i].v);
        }
    }

    vvl dis(n + 1, vl(n + 1, INF));
    F(i, 1, n) dis[i][i] = 0;

    F(i, 1, m) {
        if (!is_del[i]) {
            int u = edges[i].u, v = edges[i].v;
            ll w = edges[i].w;
            dis[u][v] = min(dis[u][v], w);
            dis[v][u] = min(dis[v][u], w);
        }
    }

    F(k, 1, n) {
        F(i, 1, n) {
            F(j, 1, n) { dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]); }
        }
    }

    vl ans;

    D(i, q, 1) {
        if (qs[i].op == 1) {
            int idx = qs[i].u;
            int u = edges[idx].u;
            int v = edges[idx].v;
            ll w = edges[idx].w;

            dis[u][v] = min(dis[u][v], w);
            dis[v][u] = min(dis[v][u], w);

            F(x, 1, n) {
                F(y, 1, n) {
                    ll d1 = dis[x][u] + w + dis[v][y];
                    ll d2 = dis[x][v] + w + dis[u][y];
                    dis[x][y] = min(dis[x][y], min(d1, d2));
                }
            }
        } else {
            int u = qs[i].u, v = qs[i].v;
            if (dis[u][v] >= INF)
                ans.pb(-1);
            else
                ans.pb(dis[u][v]);
        }
    }

    reverse(all(ans));
    for (auto v: ans)
        prt(v);
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
