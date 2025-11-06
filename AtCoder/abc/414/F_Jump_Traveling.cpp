#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define db long double
#define pb emplace_back
#define pf emplace_front
#define all(x) (x).begin(), (x).end()
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

#ifdef LOCAL
#define dbg(...) cerr << "[L" << __LINE__ << " " << __func__ << " | " << #__VA_ARGS__ << "]: ", debug_out(__VA_ARGS__)
#else
#define dbg(...) ((void) 0)
#endif

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n, k;
    rd(n, k);

    vvi g(n + 1);
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    int cnt = 0;
    vi parent(n + 1), L(n + 1), R(n + 1), dis(n + 1), seq(n + 1);
    auto dfs = [&](auto &&dfs, int u, int fa) -> void {
        parent[u] = fa;
        L[u] = ++cnt;
        seq[cnt] = u;
        for (int v: g[u]) {
            if (v == fa) {
                continue;
            }
            dis[v] = dis[u] + 1;
            dfs(dfs, v, u);
        }
        R[u] = cnt;
    };

    dfs(dfs, 1, 0);
    int mx = 0;
    F(i, 1, n) mx = max(mx, dis[i]);

    vector<set<int>> pts(mx + 1);
    F(i, 1, n) { pts[dis[i]].insert(L[i]); }

    vi ans(n + 1, -1);
    queue<int> q;

    q.push(1);
    ans[1] = 0;
    pts[dis[1]].erase(L[1]);

    auto push_nodes = [&](int l, int r, int target_depth, int current_dist) {
        if (target_depth < 0 || target_depth > mx) {
            return;
        }

        auto &s = pts[target_depth];
        for (auto it = s.lower_bound(l);;) {
            if (it == s.end() || *it > r) {
                break;
            }

            int v_dfs_order = *it;
            int v = seq[v_dfs_order];

            it = s.erase(it);

            ans[v] = current_dist + 1;
            q.push(v);
        }
    };


    while (!q.empty()) {
        int u = q.front();
        q.pop();

        int current_dist = ans[u];

        push_nodes(L[u], R[u], dis[u] + k, current_dist);
        int p = u;
        int lst = u;

        F(i, 1, k) {
            lst = p;
            p = parent[p];

            if (p == 0) {
                break;
            }

            int target_depth = dis[u] + k - 2 * i;

            if (target_depth < 0) {
                break;
            }

            push_nodes(L[p], L[lst] - 1, target_depth, current_dist);
            push_nodes(R[lst] + 1, R[p], target_depth, current_dist);
        }
    }

    prv(ans, 2);
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
