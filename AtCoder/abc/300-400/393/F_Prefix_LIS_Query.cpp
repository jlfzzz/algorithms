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

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_M = 1e5 + 5;
const int MAX_NODES = MAX_M * 60;

struct Node {
    int ls, rs;
    ll sum, mx, mn;
    ll add;
} tree[MAX_NODES];

struct Result {
    ll sum, mx, mn;
};

int root = 0;
int cnt = 0;

int new_node() {
    ++cnt;
    tree[cnt].ls = tree[cnt].rs = 0;
    tree[cnt].sum = 0;
    tree[cnt].add = 0;
    tree[cnt].mn = 0;
    tree[cnt].mx = 0;
    return cnt;
}

void apply(int &p, ll val, int len) {
    if (!p) {
        p = new_node();
    }
    tree[p].sum += val * len;
    tree[p].mx += val;
    tree[p].mn += val;
    tree[p].add += val;
}

void pushdown(int p, int l, int r) {
    if (tree[p].add == 0)
        return;
    int mid = l + (r - l) / 2;
    apply(tree[p].ls, tree[p].add, mid - l + 1);
    apply(tree[p].rs, tree[p].add, r - mid);
    tree[p].add = 0;
}

void pushup(int p) {
    tree[p].sum = tree[tree[p].ls].sum + tree[tree[p].rs].sum;
    tree[p].mx = max(tree[tree[p].ls].mx, tree[tree[p].rs].mx);
    tree[p].mn = min(tree[tree[p].ls].mn, tree[tree[p].rs].mn);
}

void update(int &p, int l, int r, int ql, int qr, int val) {
    if (!p)
        p = new_node();

    if (ql <= l && r <= qr) {
        apply(p, val, r - l + 1);
        return;
    }
    pushdown(p, l, r);
    int mid = l + (r - l) / 2;
    if (ql <= mid)
        update(tree[p].ls, l, mid, ql, qr, val);
    if (qr > mid)
        update(tree[p].rs, mid + 1, r, ql, qr, val);
    pushup(p);
}

Result query_all(int p, int l, int r, int ql, int qr) {
    if (!p)
        return {0, 0, 0};

    if (ql <= l && r <= qr) {
        return {tree[p].sum, tree[p].mx, tree[p].mn};
    }

    pushdown(p, l, r);
    int mid = l + (r - l) / 2;

    Result res = {0, (ll) -4e18, (ll) 4e18};
    bool found = false;

    if (ql <= mid) {
        res = query_all(tree[p].ls, l, mid, ql, qr);
        found = true;
    }
    if (qr > mid) {
        Result right = query_all(tree[p].rs, mid + 1, r, ql, qr);
        if (!found) {
            res = right;
        } else {
            res.sum += right.sum;
            res.mx = max(res.mx, right.mx);
            res.mn = min(res.mn, right.mn);
        }
    }
    return res;
}

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

void solve() {
    int n, q;
    rd(n, q);

    vl a(n + 1);
    rv(a, 1);

    vvp qs(n + 1);

    F(i, 1, q) {
        ll r, x;
        rd(r, x);
        qs[r].pb(x, i);
    }

    vi ans(q + 1);
    const int MAX_V = 1e9;

    F(i, 1, n) {
        ll mx = 0;
        Result res = query_all(root, 1, MAX_V, 1, a[i] - 1);
        mx = max(0LL, res.mx);

        ll nmx = mx + 1;

        ll cur = 0;
        Result t = query_all(root, 1, MAX_V, a[i], a[i]);
        cur = max(0LL, t.mx);

        if (nmx > cur) {
            update(root, 1, MAX_V, a[i], a[i], nmx - cur);
        }

        for (auto [x, id]: qs[i]) {
            Result res = query_all(root, 1, MAX_V, 1, x);
            ans[id] = max(0LL, res.mx);
        }
    }

    F(i, 1, q) { prt(ans[i]); }
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
