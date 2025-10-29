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
#define F(i, j, k) for (int(i) = (j); (i) <= (k); (i)++)
#define D(i, j, k) for (int(i) = (j); (i) >= (k); (i)--)
#define SZ(a) ((int) (a).size())
#define prq priority_queue
#define fi first
#define se second
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int inf = 0x3f3f3f3f;

namespace utils {
    void dbg() { cerr << "\n"; }

    template<typename T, typename... Args>
    void dbg(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        dbg(args...);
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

using namespace utils;

constexpr int N = 1e6 + 5;

int Multitest = 0;

void init() {}

struct Node {
    int ls, rs; // child indices in pool
    ll sum; // sum of working days in this segment
    int lazy; // -1: no tag; 0/1: assign
};

static const int MAXNODE = 3200000; // ~3.2M nodes, enough for 1e5 ops on 1e9
static Node tree[MAXNODE];
static int tot, root;

inline void apply(int o, int seg_len, int val) {
    tree[o].sum = 1LL * seg_len * val;
    tree[o].lazy = val;
}

inline void pushdown(int o, int l, int r) {
    if (tree[o].lazy == -1 || l == r)
        return;
    int mid = (l + r) >> 1;
    if (!tree[o].ls)
        tree[o].ls = ++tot;
    if (!tree[o].rs)
        tree[o].rs = ++tot;
    apply(tree[o].ls, mid - l + 1, tree[o].lazy);
    apply(tree[o].rs, r - mid, tree[o].lazy);
    tree[o].lazy = -1;
}

void insert(int &o, int l, int r, int ql, int qr, int val) {
    if (!o) {
        o = ++tot;
        tree[o].ls = tree[o].rs = 0;
        tree[o].sum = 0;
        tree[o].lazy = -1;
    }
    if (ql <= l && r <= qr) {
        apply(o, r - l + 1, val);
        return;
    }
    pushdown(o, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid)
        insert(tree[o].ls, l, mid, ql, qr, val);
    if (qr > mid)
        insert(tree[o].rs, mid + 1, r, ql, qr, val);
    ll left_sum = tree[o].ls ? tree[tree[o].ls].sum : 0;
    ll right_sum = tree[o].rs ? tree[tree[o].rs].sum : 0;
    tree[o].sum = left_sum + right_sum;
}


void solve() {
    tot = 0;
    int n, q;
    rd(n, q);
    root = ++tot;
    tree[root].ls = tree[root].rs = 0;
    tree[root].sum = n;
    tree[root].lazy = 1; // whole range initially working
    F(i, 1, q) {
        int l, r, k;
        rd(l, r, k);
        insert(root, 1, n, l, r, k == 1 ? 0 : 1);
        prt(tree[root].sum);
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
