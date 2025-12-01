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
    int n;
    rd(n);

    vi a(n + 1);
    vp g(n + 1);
    vi deg(n + 1, 0);

    F(i, 1, n) {
        int x, y, z;
        rd(x, y, z);

        a[i] = x;
        g[i].first = y;
        g[i].second = z;

        if (y != -1)
            deg[y]++;
        if (z != -1)
            deg[z]++;
    }

    int root = 1;
    F(i, 1, n) {
        if (deg[i] == 0)
            root = i;
    }

    vi sz(n + 1);
    auto dfs1 = [&](this auto &&self, int u) -> void {
        sz[u] = 1;
        auto [x, y] = g[u];
        if (x != -1) {
            self(x);
            sz[u] += sz[x];
        }
        if (y != -1) {
            self(y);
            sz[u] += sz[y];
        }
    };
    dfs1(root);

    auto dfs2 = [&](this auto &&self, int u) -> multiset<pii> * {
        if (g[u].first == -1 && g[u].second == -1) {
            auto *st = new multiset<pii>;
            st->insert({a[u], u});
            return st;
        }

        int heavy = -1, light = -1;
        int l = g[u].first, r = g[u].second;

        if (l == -1)
            heavy = r;
        else if (r == -1)
            heavy = l;
        else
            heavy = (sz[l] > sz[r] ? l : r);

        light = (heavy == l ? r : l);

        multiset<pii> *st = self(heavy);

        if (heavy == l) {
            auto it = st->lower_bound({a[u], -INF});
            st->erase(it, st->end());
        } else {
            auto it = st->upper_bound({a[u], INF});
            st->erase(st->begin(), it);
        }

        if (light != -1) {
            multiset<pii> *small = self(light);

            if (light == l) {
                auto it = small->lower_bound({a[u], -INF});
                small->erase(it, small->end());
            } else {
                auto it = small->upper_bound({a[u], INF});
                small->erase(small->begin(), it);
            }

            for (auto &x: *small)
                st->insert(x);
            delete small;
        }

        st->insert({a[u], u});
        return st;
    };

    multiset<pii> *st = dfs2(root);
    int cnt = 0;
    F(i, 1, n) {
        auto it = st->lower_bound({a[i], -INF});
        if (it != st->end() && it->first == a[i]) {
            cnt++;
        }
    }

    prt(n - cnt);
    delete st;
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
