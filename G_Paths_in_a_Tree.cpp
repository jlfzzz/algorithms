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

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);

    vvi g(n + 1);
    F(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    vi mx1(n + 1), son(n + 1), depth(n + 1);
    vi pa(n + 1);

    auto dfs1 = [&](this auto &&dfs, int u, int fa, int d) -> void {
        depth[u] = d;
        pa[u] = fa;
        mx1[u] = u;
        son[u] = 0;
        for (auto &v: g[u]) {
            if (v == fa) {
                continue;
            }

            dfs(v, u, d + 1);
            if (depth[mx1[v]] > depth[mx1[u]]) {
                mx1[u] = mx1[v];
                son[u] = v;
            }
        }
    };

    dfs1(1, 0, 1);

    prq<pii> pq;
    pq.push({depth[mx1[1]] - depth[1], 1});
    int rem = n;

    auto Get = [&](int u, int v) {
        vi p1, p2;
        int x = u;
        while (x) {
            p1.pb(x);
            x = pa[x];
        }
        x = v;
        while (x) {
            p2.pb(x);
            x = pa[x];
        }
        reverse(all(p1));
        reverse(all(p2));
        int lca = 0;
        int len = min(SZ(p1), SZ(p2));
        F(i, 0, len - 1) {
            if (p1[i] == p2[i]) {
                lca = p1[i];
            } else {
                break;
            }
        }
        vi res;
        x = u;
        while (x != lca) {
            res.pb(x);
            x = pa[x];
        }
        res.pb(lca);
        vi temp;
        x = v;
        while (x != lca) {
            temp.pb(x);
            x = pa[x];
        }
        reverse(all(temp));
        res.insert(res.end(), all(temp));
        return res;
    };

    auto calc = [&](int u, int v) {
        vi p = Get(u, v);
        int l = 0, r = SZ(p) - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            cout << "? " << p[0] << " " << p[mid] << endl;
            int res;
            rd(res);
            if (res == 1) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        cout << "! " << p[l] << endl;
    };

    while (!pq.empty()) {
        if (SZ(pq) == 1) {
            auto [h, u] = pq.top();
            pq.pop();
            int v = mx1[u];
            int len = depth[v] - depth[u] + 1;

            if (len == rem) {
                calc(u, v);
                return;
            }

            cout << "? " << u << " " << v << endl;
            int res;
            rd(res);
            if (res == 1) {
                calc(u, v);
                return;
            } else {
                rem -= len;
                int curr = u;
                while (true) {
                    for (auto &nxt: g[curr]) {
                        if (nxt != pa[curr] && nxt != son[curr]) {
                            pq.push({depth[mx1[nxt]] - depth[nxt], nxt});
                        }
                    }
                    if (curr == v)
                        break;
                    curr = son[curr];
                }
            }
        } else {
            auto [h1, u] = pq.top();
            pq.pop();
            auto [h2, v] = pq.top();
            pq.pop();

            int l1 = mx1[u], l2 = mx1[v];
            cout << "? " << l1 << " " << l2 << endl;
            int res;
            rd(res);

            if (res == 1) {
                calc(l1, l2);
                return;
            } else {
                // 排除两条重链
                rem -= (depth[l1] - depth[u] + 1);
                rem -= (depth[l2] - depth[v] + 1);

                auto add = [&](int root, int leaf) {
                    int curr = root;
                    while (true) {
                        for (auto &nxt: g[curr]) {
                            if (nxt != pa[curr] && nxt != son[curr]) {
                                pq.push({depth[mx1[nxt]] - depth[nxt], nxt});
                            }
                        }
                        if (curr == leaf) {
                            break;
                        }

                        curr = son[curr];
                    }
                };
                add(u, l1);
                add(v, l2);
            }
        }
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
