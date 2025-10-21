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
    int n, m;
    rd(n, m);

    vector<vector<int>> g(n);
    for (int i: range(m)) {
        int u, v;
        rd(u, v);
        u--,v--;
        g[u].pb(v);
        g[v].pb(u);
    }

    vector<pair<int, int>> edges;
    for (int i = 0; i < n; i++) {
        if (g[i].size() >= 4) {
            vector<bool> nei(n, false);
            for (int j: g[i]) {
                nei[j] = true;
            }
            vector<int> pv(n, -1);
            pv[i] = -2;
            int win = -1;
            for (int j: g[i]) {
                if (pv[j] == -1) {
                    vector<int> que(1, j);
                    pv[j] = i;
                    for (int b = 0; b < (int) que.size(); b++) {
                        for (int to: g[que[b]]) {
                            if (pv[to] == -1) {
                                que.push_back(to);
                                pv[to] = que[b];
                                if (win == -1 && nei[to]) {
                                    win = to;
                                }
                            }
                        }
                    }
                }
            }
            if (win != -1) {
                edges.emplace_back(i, win);
                int x = win;
                while (x != i) {
                    edges.emplace_back(x, pv[x]);
                    x = pv[x];
                }
                vector<bool> used(n, false);
                for (auto &e: edges) {
                    used[e.first] = true;
                    used[e.second] = true;
                }
                vector<int> rest;
                for (int y: g[i]) {
                    if (!used[y]) {
                        rest.push_back(y);
                    }
                }
                assert(rest.size() >= 2);
                edges.emplace_back(i, rest[0]);
                edges.emplace_back(i, rest[1]);
                break;
            }
        }
    }
    if (edges.empty()) {
        cout << "NO" << '\n';
    } else {
        cout << "YES" << '\n';
        cout << edges.size() << '\n';
        for (auto &e: edges) {
            cout << e.first + 1 << " " << e.second + 1 << '\n';
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
