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
    int n;
    rd(n);

    vector<vector<int>> g(n + 1);
    for (int _: range(n - 1)) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    vector<int> dis(n + 1), in(n + 1), parent(n + 1);

    auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }

            dis[v] = dis[u] + 1;
            parent[v] = u;
            dfs(v, u);
        }
    };

    dfs(1, 0);
    vector<int> path;
    {
        int t = n;
        while (parent[t]) {
            in[t] = 1;
            path.pb(t);
            t = parent[t];
        }
        path.pb(t);
        in[t] = 1;
        ranges::reverse(path);
    }

    priority_queue<pair<int, int>> pq1, pq0;
    for (int i: range(1, n)) {
        if (!in[i]) {
            if (dis[i] & 1) {
                pq1.emplace(dis[i], i);
            } else {
                pq0.emplace(dis[i], i);
            }
        }
    }

    vector<pii> ans;
    int ts = 0;
    while (!pq0.empty() || !pq1.empty()) {
        if (ts & 1) {
            if (!pq0.empty()) {
                auto t0 = pq0.top();
                int u = t0.second;
                if (!pq1.empty() && t0.first < pq1.top().first) {

                } else {
                    pq0.pop();
                    ans.eb(2, u);
                }
            }
        } else {
            if (!pq1.empty()) {
                auto t1 = pq1.top();
                int u = t1.second;
                if (!pq0.empty() && t1.first < pq0.top().first) {

                } else {
                    pq1.pop();
                    ans.emplace_back(2, u);
                }
            }
        }

        ans.emplace_back(1, -1);
        ts++;
    }

    if (ts % 2 == 0) {
        ans.emplace_back(1, -1);
        ts++;
    }

    for (int x: path) {
        if (x == n) {
            break;
        }

        ans.eb(2, x);
        ans.eb(1, -1);
    }

    prt(ans.size());
    for (auto &[x, y]: ans) {
        if (x == 2) {
            prt(x, y);
        } else {
            prt(x);
        }
    }
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
