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
#define L(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)

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

constexpr int N = 1e5 + 5;

struct Node {
    ll val = INF;
};

class PST {
private:
    int n, ts;
    std::vector<int> lc, rc;
    std::vector<Node> tree;

    void newnode(int pre, int cur) {
        lc[cur] = lc[pre];
        rc[cur] = rc[pre];
        tree[cur] = tree[pre];
    }

    Node merge(const Node &left, const Node &right) { return Node{min(left.val, right.val)}; }

    int _build(int l, int r) {
        int cur = ++ts;
        tree[cur] = Node{INF};
        if (l == r) {
            return cur;
        }
        int m = (l + r) / 2;
        lc[cur] = _build(l, m);
        rc[cur] = _build(m + 1, r);
        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    int _update(int pre, int l, int r, int pos, ll val) {
        int cur = ++ts;
        newnode(pre, cur);
        if (l == r) {
            tree[cur].val = val;
            return cur;
        }
        int m = (l + r) / 2;
        if (pos <= m)
            lc[cur] = _update(lc[pre], l, m, pos, val);
        else
            rc[cur] = _update(rc[pre], m + 1, r, pos, val);

        tree[cur] = merge(tree[lc[cur]], tree[rc[cur]]);
        return cur;
    }

    ll _query(int cur, int l, int r, int ql, int qr) {
        if (ql > r || qr < l)
            return INF;
        if (ql <= l && r <= qr)
            return tree[cur].val;
        int m = (l + r) / 2;
        return min(_query(lc[cur], l, m, ql, qr), _query(rc[cur], m + 1, r, ql, qr));
    }

public:
    PST(int n) : n(n), ts(0), lc(40 * n + 5), rc(40 * n + 5), tree(40 * n + 5) {}

    int build() { return _build(1, n); }

    int update(int pre_version, int pos, ll val) { return _update(pre_version, 1, n, pos, val); }

    ll query(int cur_version, int l, int r) { return _query(cur_version, 1, n, l, r); }
};

int Multitest = 0;
vi g[N];
int tin[N], tout[N], dep[N];
int ts;
ll a[N];
vi depth[N];
int roots[N];

void dfs(int u, int p, int d) {
    tin[u] = ++ts;
    dep[u] = d;
    depth[d].push_back(u);
    for (int v: g[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
    tout[u] = ts;
}

void init() {}

void solve() {
    int n, r;
    rd(n, r);
    L(i, 1, n) rd(a[i]);

    ts = 0;
    L(i, 1, n - 1) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    dfs(r, 0, 1);
    int mxD = 0;
    L(i, 1, n) mxD = max(mxD, dep[i]);

    PST pst(n);
    roots[0] = pst.build();

    L(d, 1, mxD) {
        int t = roots[d - 1];
        for (int u: depth[d]) {
            t = pst.update(t, tin[u], a[u]);
        }
        roots[d] = t;
    }

    int m;
    rd(m);
    int last = 0;
    while (m--) {
        int p, q;
        rd(p, q);
        int x = (p + last) % n + 1;
        int k = (q + last) % n;

        int mx = min(mxD, dep[x] + k);

        ll ans = pst.query(roots[mx], tin[x], tout[x]);

        prt(ans);
        last = ans % n;
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
