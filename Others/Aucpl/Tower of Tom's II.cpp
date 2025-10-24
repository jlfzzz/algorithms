#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

// https://aucpl.com/problem/toweroftomsii

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
    void rd(T &x) {
        cin >> x;
    }

    template<typename T, typename... Args>
    void rd(T &x, Args &...args) {
        cin >> x;
        rd(args...);
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

using ll = long long;
using Flow = long long;
const ll INF = 1e18;

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

int Multitest = 0;

void solve() {
    int n;
    rd(n);
    string s;
    rd(s);
    if (s.size() != n) {
        prt(-1);
        return;
    }

    int cntT = 0, cntH = 0, cntB = 0, cntO = 0;
    for (char c: s) {
        if (c == 'T') {
            cntT += 1;
        } else if (c == 'H') {
            cntH += 1;
        } else if (c == 'b') {
            cntB += 1;
        } else if (c == 'o') {
            cntO += 1;
        } else {
            prt(-1);
            return;
        }
    }

    int needT = n / 3;
    if (cntT != needT) {
        prt(-1);
        return;
    }
    if (!(cntH == 0 || cntH == 1)) {
        prt(-1);
        return;
    }
    if (cntB < 1 || cntO < 1) {
        prt(-1);
        return;
    }


    int N = 2 * n + 2;
    int S = 0;
    int T = 2 * n + 1;
    MCMF mcmf(N);

    for (int i = 0; i < n; ++i) {
        mcmf.addEdge(S, 1 + i, 1, 0);
    }

    auto check = [&](char ch, int pos, int n, int cntH) -> bool {
        int oneBased = pos + 1;
        bool isTslot = (oneBased % 3 == 0);
        if (ch == 'T') {
            if (isTslot) {
                return true;
            } else {
                return false;
            }
        }
        if (isTslot) {
            return false;
        }
        if (ch == 'H') {
            if (cntH == 1 && pos == 0) {
                return true;
            } else {
                return false;
            }
        }
        if (ch == 'b') {
            if (pos != 0 && pos != n - 1) {
                return true;
            } else {
                return false;
            }
        }
        if (ch == 'o') {
            if (cntH == 1 && pos == 0) {
                return false;
            } else {
                return true;
            }
        }
        return false;
    };

    for (int i = 0; i < n; ++i) {
        char ch = s[i];
        for (int j = 0; j < n; ++j) {
            if (check(ch, j, n, cntH)) {
                int cost = abs(i - j);
                mcmf.addEdge(1 + i, 1 + n + j, 1, cost);
            } else {
                continue;
            }
        }
    }
    for (int j = 0; j < n; ++j) {
        mcmf.addEdge(1 + n + j, T, 1, 0);
    }

    auto res = mcmf.minCostMaxFlow(S, T);
    if (res.first != n) {
        prt(-1);
    } else {
        prt(res.second);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    if (Multitest)
        rd(T);
    while (T--)
        solve();
    return 0;
}
