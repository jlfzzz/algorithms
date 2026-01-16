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
    ll n, k;
    rd(n, k);
    vi v0, v2, v1;

    F(i, 1, n) {
        int x;
        rd(x);
        if (x % 4 == 0)
            v0.pb(i);
        else if (x % 2 == 0)
            v2.pb(i);
        else
            v1.pb(i);
    }

    if (n == 1) {
        prt(1);
        return;
    }

    if (v0.empty()) {
        if (!v1.empty()) {
            prt(-1);
        } else {
            prt(v2[0]);
            F(i, 0, SZ(v2) - 2) { prt(v2[i], v2[i + 1]); }
        }
        return;
    }

    int num_bridges = min(SZ(v1), SZ(v0) - 1);

    int rem_v1 = SZ(v1) - num_bridges;

    int bonus_root = (v2.empty() && rem_v1 > 0) ? 1 : 0;
    rem_v1 -= bonus_root;

    ll capacity = 1LL * (SZ(v0) - 1) * (k - 1) + k;

    if (rem_v1 > capacity) {
        prt(-1);
        return;
    }

    vi bridge_nodes, leaf_nodes;
    int root_odd = -1;

    int v1_idx = 0;
    F(i, 1, num_bridges) bridge_nodes.pb(v1[v1_idx++]);
    if (bonus_root)
        root_odd = v1[v1_idx++];
    while (v1_idx < SZ(v1))
        leaf_nodes.pb(v1[v1_idx++]);

    int final_root;
    if (!v2.empty())
        final_root = v2[0];
    else if (bonus_root)
        final_root = root_odd;
    else
        final_root = v0[0];

    prt(final_root);

    if (!v2.empty()) {
        F(i, 0, SZ(v2) - 2) prt(v2[i], v2[i + 1]);
        prt(v2.back(), v0[0]);
    } else if (bonus_root) {
        prt(root_odd, v0[0]);
    }

    F(i, 0, SZ(v0) - 2) {
        if (i < SZ(bridge_nodes)) {
            prt(v0[i], bridge_nodes[i]);
            prt(bridge_nodes[i], v0[i + 1]);
        } else {
            prt(v0[i], v0[i + 1]);
        }
    }

    int cur_leaf = 0;
    for (int u: v0) {
        ll free = (u == v0.back()) ? k : k - 1;

        while (free > 0 && cur_leaf < SZ(leaf_nodes)) {
            prt(u, leaf_nodes[cur_leaf++]);
            free--;
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
