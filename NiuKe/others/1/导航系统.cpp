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

class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;
    int count;

    explicit UnionFind(const int n) : count(n) {
        parent.resize(n);
        rank.resize(n);
        ranges::fill(rank, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            return false;
        }

        if (rank[root_x] == rank[root_y]) {
            parent[root_x] = root_y;
            rank[root_y] += 1;
        } else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
        } else {
            parent[root_x] = root_y;
        }
        count--;
        return true;
    }
};

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n0;
    rd(n0);
    vvl a0(n0 + 1, vl(n0 + 1));
    F(i, 1, n0) {
        F(j, 1, n0) { rd(a0[i][j]); }
    }
    F(i, 1, n0) {
        if (a0[i][i] != 0) {
            prt("No");
            return;
        }
    }
    F(i, 1, n0) {
        F(j, i + 1, n0) {
            if (a0[i][j] != a0[j][i]) {
                prt("No");
                return;
            }
            if (a0[i][j] < 0) {
                prt("No");
                return;
            }
        }
    }
    F(k, 1, n0) {
        F(i, 1, n0) {
            if (i == k) {
                continue;
            }
            F(j, 1, n0) {
                if (j == k || j == i) {
                    continue;
                }
                if (a0[i][j] > a0[i][k] + a0[k][j]) {
                    prt("No");
                    return;
                }
            }
        }
    }
    if (n0 == 1) {
        prt("Yes");
        return;
    }
    UnionFind ufz(n0);
    F(i, 1, n0) {
        F(j, i + 1, n0) {
            if (a0[i][j] == 0) {
                ufz.unite(i - 1, j - 1);
            }
        }
    }
    unordered_map<int, int> mp;
    mp.reserve(n0 * 2);
    int m = 0;
    vector<int> comp_root(n0 + 1);
    vector<int> comp_id(n0 + 1);
    F(i, 1, n0) {
        int r = ufz.find(i - 1);
        comp_root[i] = r;
        auto it = mp.find(r);
        if (it == mp.end()) {
            mp[r] = ++m;
            comp_id[i] = m;
        } else {
            comp_id[i] = it->second;
        }
    }
    vector<vi> members(m + 1);
    F(i, 1, n0) {
        int id = comp_id[i];
        members[id].pb(i);
    }
    if (m == 1) {
        F(i, 1, n0) {
            F(j, 1, n0) {
                if (a0[i][j] != 0) {
                    prt("No");
                    return;
                }
            }
        }
        prt("Yes");
        F(i, 1, n0 - 1) { prt(0); }
        return;
    }
    int n = m;
    vvl a(n + 1, vl(n + 1));
    F(i, 1, n) { a[i][i] = 0; }
    vl rep(n + 1);
    F(c, 1, n) { rep[c] = members[c][0]; }
    F(i, 1, n) {
        F(j, i + 1, n) {
            ll d = a0[rep[i]][rep[j]];
            a[i][j] = d;
            a[j][i] = d;
        }
    }
    F(c1, 1, n) {
        F(c2, c1 + 1, n) {
            ll d = a[c1][c2];
            if (d <= 0) {
                prt("No");
                return;
            }
            for (int x: members[c1]) {
                for (int y: members[c2]) {
                    if (a0[x][y] != d) {
                        prt("No");
                        return;
                    }
                }
            }
        }
    }
    vector<tuple<int, int, ll>> es_comp;
    F(i, 1, n) {
        F(j, i + 1, n) {
            bool direct = true;
            F(k, 1, n) {
                if (k == i || k == j) {
                    continue;
                }
                if (a[i][j] == a[i][k] + a[k][j]) {
                    direct = false;
                    break;
                }
            }
            if (direct) {
                es_comp.pb(i, j, a[i][j]);
            }
        }
    }
    if (SZ(es_comp) != n - 1) {
        prt("No");
        return;
    }
    UnionFind uf(n);
    for (auto &e: es_comp) {
        int u, v;
        ll w;
        tie(u, v, w) = e;
        uf.unite(u - 1, v - 1);
    }
    int comp = 0;
    F(i, 0, n - 1) {
        if (uf.find(i) == i) {
            comp++;
        }
    }
    if (comp != 1) {
        prt("No");
        return;
    }
    vector<vector<pair<int, ll>>> g(n0 + 1);
    F(c, 1, n) {
        int r = (int) rep[c];
        if (SZ(members[c]) >= 2) {
            F(idx, 1, SZ(members[c]) - 1) {
                int x = members[c][idx];
                g[r].pb(x, 0);
                g[x].pb(r, 0);
            }
        }
    }
    for (auto &e: es_comp) {
        int cu, cv;
        ll w;
        tie(cu, cv, w) = e;
        int u = (int) rep[cu];
        int v = (int) rep[cv];
        g[u].pb(v, w);
        g[v].pb(u, w);
    }
    vvl dist(n0 + 1, vl(n0 + 1));
    F(s, 1, n0) {
        auto dfs = [&](auto self, int u, int p, ll cur) -> void {
            dist[s][u] = cur;
            for (auto &pr: g[u]) {
                int v = pr.first;
                ll w = pr.second;
                if (v == p) {
                    continue;
                }
                self(self, v, u, cur + w);
            }
        };
        dfs(dfs, s, 0, 0);
    }
    F(i, 1, n0) {
        F(j, 1, n0) {
            if (dist[i][j] != a0[i][j]) {
                prt("No");
                return;
            }
        }
    }
    prt("Yes");
    vl wv;
    F(c, 1, n) {
        int sz = SZ(members[c]);
        if (sz >= 2) {
            F(t, 1, sz - 1) { wv.pb(0); }
        }
    }
    for (auto &e: es_comp) {
        int cu, cv;
        ll w;
        tie(cu, cv, w) = e;
        wv.pb(w);
    }
    ranges::sort(wv);
    for (ll w: wv) {
        prt(w);
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
