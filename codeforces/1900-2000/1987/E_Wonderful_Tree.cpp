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

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    int n;
    rd(n);

    vl a(n + 1);
    rv(a, 1);

    vvi g(n + 1);
    F(i, 2, n) {
        int p;
        rd(p);
        g[p].pb(i);
    }

    vl in(n + 1), out(n + 1), depth(n + 1), childSum(n + 1);
    vvl layers(n + 1);
    int ts = 0;
    ll ans = 0;

    auto isSon = [&](int u, int v) { return in[u] < in[v] && out[u] >= out[v]; };

    // 启发式合并 nlog^2
    struct Node {
        ll depth, w;
        bool operator<(const Node &other) const { return this->depth > other.depth; }
    };

    vl sz(n + 1);
    auto dfs1 = [&](this auto &&dfs, int u) -> void {
        sz[u] = 1;
        for (int v: g[u]) {
            dfs(v);
            sz[u] += sz[v];
        }
    };

    auto dfs2 = [&](this auto &&dfs, int u) -> priority_queue<Node> * {
        if (g[u].empty()) {
            priority_queue<Node> *pq = new priority_queue<Node>;
            pq->emplace(depth[u], INF);
            return pq;
        }

        int son = -1;
        ll sum = 0;
        for (int v: g[u]) {
            if (son == -1 || sz[v] > sz[son]) {
                son = v;
            }
        }

        depth[son] = depth[u] + 1;
        priority_queue<Node> *pq = dfs(son);
        sum += a[son];

        for (int v: g[u]) {
            if (v == son) {
                continue;
            }

            depth[v] = depth[u] + 1;
            priority_queue<Node> *temp = dfs(v);
            while (!temp->empty()) {
                pq->push(temp->top());
                temp->pop();
            }
            delete temp;
            sum += a[v];
        }

        if (a[u] > sum) {
            ll t = a[u] - sum;
            while (t) {
                auto [d, w] = pq->top();
                pq->pop();
                ll need = min(w, t);
                ll cost = (d - depth[u]) * need;
                ans += cost;
                if (w - need > 0) {
                    pq->emplace(d, w - need);
                }

                t -= need;
            }
        } else {
            pq->emplace(depth[u], sum - a[u]);
        }

        return pq;
    };

    // n^2贪心
    auto dfs = [&](this auto &&dfs, int u) -> void {
        in[u] = ++ts;

        if (g[u].empty()) {
            out[u] = ts;
            return;
        }
        ll sum = 0;

        for (int v: g[u]) {
            depth[v] = depth[u] + 1;
            layers[depth[v]].pb(v);
            dfs(v);
            sum += a[v];
        }

        childSum[u] = sum;
        out[u] = ts;
        if (a[u] > sum) {
            childSum[u] = a[u];
            ll curD = depth[u];
            ll t = a[u];
            F(d, depth[u] + 1, n) {
                if (layers[d].empty() || t <= sum) {
                    break;
                }

                bool haveLeaf = false;
                for (int v: layers[d]) {
                    if (!isSon(u, v)) {
                        continue;
                    }
                    // dbg(v);
                    if (g[v].empty()) {
                        haveLeaf = true;
                    }
                }

                if (haveLeaf) {
                    ans += (d - curD) * (t - sum);
                    t = sum;
                    break;
                }

                for (int v: layers[d]) {
                    if (!isSon(u, v)) {
                        continue;
                    }

                    if (a[v] < childSum[v]) {
                        ll mn = min(childSum[v] - a[v], t - sum);
                        ans += (d - curD) * mn;
                        t -= mn;
                        a[v] += mn;
                    }
                }
            }
        }
    };

    dfs1(1);
    dfs2(1);

    prt(ans);
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
