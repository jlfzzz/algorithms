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

int Multitest = 0;

void init() {}

struct DSU {
    vector<int> parent;
    int cnt;

    DSU(int n) {
        parent.resize(n + 1);
        iota(all(parent), 0);
        cnt = n;
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            cnt--;
            return true;
        }
        return false;
    }

    bool same(int i, int j) { return find(i) == find(j); }

    void add_node() { cnt++; }
};

struct Edge {
    ll u, v, w;
    bool operator<(const Edge &other) const { return w > other.w; }
};

void solve() {
    int n, q;
    rd(n, q);

    vector<pii> pts(n + q + 1);
    F(i, 1, n) { rd(pts[i]); }

    auto calc = [&](int i, int j) { return abs(pts[i].first - pts[j].first) + abs(pts[i].second - pts[j].second); };

    priority_queue<Edge> pq;

    F(i, 1, n) {
        F(j, i + 1, n) { pq.push({(ll) i, (ll) j, calc(i, j)}); }
    }
    DSU dsu(n + q);
    dsu.cnt = n;

    int current_n = n;

    while (q--) {
        int op;
        rd(op);

        if (op == 1) {
            ll a, b;
            rd(a, b);
            current_n++;
            pts[current_n] = {a, b};
            dsu.add_node();

            F(i, 1, current_n - 1) { pq.push({(ll) i, (ll) current_n, calc(i, current_n)}); }

        } else if (op == 2) {
            while (!pq.empty()) {
                Edge e = pq.top();
                if (dsu.same(e.u, e.v)) {
                    pq.pop();
                } else {
                    break;
                }
            }

            if (dsu.cnt == 1 || pq.empty()) {
                prt(-1);
            } else {
                ll k = pq.top().w;
                prt(k);

                while (!pq.empty() && pq.top().w == k) {
                    Edge e = pq.top();
                    pq.pop();
                    dsu.unite(e.u, e.v);
                }
            }

        } else {
            int u, v;
            rd(u, v);
            if (dsu.same(u, v))
                prt("Yes");
            else
                prt("No");
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
