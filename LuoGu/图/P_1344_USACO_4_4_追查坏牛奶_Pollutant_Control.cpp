#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace utils {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
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
    void prt_vec(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            if (i > start_index)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename End, typename... Args>
    void prt_end(const End &end, const Args &...args) {
        ((cout << args << " "), ...);
        cout << end;
    }

    template<typename... Args>
    void prt_endl(const Args &...args) {
        ((cout << args << " "), ...);
        cout << endl;
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
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }

    struct range : ranges::view_base {
        struct Iterator {
            using iterator_category = random_access_iterator_tag;
            using value_type = long long;
            using difference_type = ptrdiff_t;
            ll val, d;
            Iterator() = default;
            Iterator(ll val, ll d) : val(val), d(d) {};
            value_type operator*() const { return val; }
            Iterator &operator++() { return val += d, *this; }
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            Iterator &operator--() { return val -= d, *this; }
            Iterator operator--(int) {
                Iterator tmp = *this;
                --(*this);
                return tmp;
            }
            difference_type operator-(const Iterator &other) const { return (val - other.val) / d; }
            bool operator==(const Iterator &other) const { return val == other.val; }
        };
        Iterator Begin, End;
        explicit range(ll n) : Begin(0, 1), End(max(n, ll{0}), 1) {};
        range(ll a, ll b, ll d = ll(1)) : Begin(a, d), End(b, d) {
            ll cnt = b == a or (b - a > 0) != (d > 0) ? 0 : (b - a) / d + bool((b - a) % d);
            End.val = a + max(cnt, ll(0)) * d;
        };
        [[nodiscard]] Iterator begin() const { return Begin; }
        [[nodiscard]] Iterator end() const { return End; };
        [[nodiscard]] ptrdiff_t size() const { return End - Begin; }
    };
} // namespace utils

using namespace utils;

#define int ll


using ll = long long;
using Flow = long long;

// removed duplicate using declarations

struct Edge {
    int to, rev;
    Flow cap;
    Flow original_cap; // 添加原始容量字段
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
int Multitest = 0;

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    Dinic dinic1(n);
    ll B = m + 1; // 大权重，先最小化费用，再最小化边数

    // struct Info {
    //     int s, e, c;
    // };
    // vector<Info> arr;
    For(i, m) {
        int s, e, c;
        rd(s, e, c);
        dinic1.add(s, e, c * B + 1);
    }

    auto tot = dinic1.maxFlow(1, n);
    auto ans1 = tot / B; // 最小费用
    auto ans2 = tot % B; // 在最小费用下的最少边数

    prt(ans1, ans2);
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
