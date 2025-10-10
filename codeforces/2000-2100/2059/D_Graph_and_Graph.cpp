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

int Multitest = 1;

void init() {}

void solve() {
    int n, s1, s2;
    rd(n, s1, s2);

    vector<vector<int>> g1(n + 1), g2(n + 1);

    int m1;
    rd(m1);
    For(i, m1) {
        int u, v;
        rd(u, v);
        g1[u].pb(v);
        g1[v].pb(u);
    }

    int m2;
    rd(m2);
    For(i, m2) {
        int u, v;
        rd(u, v);
        g2[u].pb(v);
        g2[v].pb(u);
    }

    auto bfs1 = [&](vector<vector<int>> &g, int start) -> vector<vector<int>> {
        vector<vector<int>> dis(n + 1, vector<int>(2, -1));

        struct Info {
            int u, d, flag;
        };

        deque<Info> dq;
        dq.emplace_back(start, 0, 0);
        while (!dq.empty()) {
            auto [u, d, flag] = dq.front();
            dq.pop_front();

            for (int v: g[u]) {
                int nflag = !flag;
                if (dis[v][nflag] == -1) {
                    dis[v][nflag] = d + 1;
                    dq.emplace_back(v, d + 1, nflag);
                }
            }
        }

        return dis;
    };

    auto dis1 = bfs1(g1, s1);
    auto dis2 = bfs1(g2, s2);

    vector<char> good(n + 1, 0);
    for (int i: range(1, n + 1)) {
        set<int> have;
        for (int v: g1[i]) {
            have.insert(v);
        }
        for (int v: g2[i]) {
            if (have.contains(v)) {
                good[i] = 1;
                break;
            }
        }
    }

    vector<vector<int>> dis(n + 1, vector<int>(n + 1, -inf));
    int ans = -inf;
    auto dij = [&]() -> void {
        vector<vector<int>> dist(n + 1, vector<int>(n + 1, inf));
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        dist[s1][s2] = 0;
        pq.emplace(0, s1, s2);

        while (!pq.empty()) {
            auto [d, x, y] = pq.top();
            pq.pop();
            if (d != dist[x][y])
                continue;

            if (x == y && good[x]) {
                ans = d;
                return;
            }

            for (int u: g1[x]) {
                for (int v: g2[y]) {
                    int nd = d + llabs(u - v);
                    if (nd < dist[u][v]) {
                        dist[u][v] = nd;
                        pq.emplace(nd, u, v);
                    }
                }
            }
        }
    };

    bool needDij = false;
    for (int i: range(1, n + 1)) {
        if (i == s1) {
            continue;
        }

        if (dis1[i][0] != -1 && dis2[i][0] != -1) {
            set<int> have;
            for (int v: g1[i]) {
                have.insert(v);
            }

            bool flag = false;
            for (int v: g2[i]) {
                if (have.contains(v)) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                needDij = true;
            }
        }

        if (dis1[i][1] != -1 && dis2[i][1] != -1) {
            set<int> have;
            for (int v: g1[i]) {
                have.insert(v);
            }

            bool flag = false;
            for (int v: g2[i]) {
                if (have.contains(v)) {
                    flag = true;
                    break;
                }
            }

            if (flag) {
                needDij = true;
            }
        }
    }

    if (needDij) {
        dij();
    }

    if (ans == -inf) {
        ans = -1;
    }

    prt(ans);
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
