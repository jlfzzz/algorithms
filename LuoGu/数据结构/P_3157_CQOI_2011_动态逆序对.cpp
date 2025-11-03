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

constexpr int N = 1e5 + 5, M = 3e7 + 10;

int lb(int x) { return x & -x; }

int bit[N];
int root[N], ls[M], rs[M], sum[M];
int pos[N], a[N];
int tot;
int n, m;

void upd(int &rt, int l, int r, int pos, int val) {
    if (!rt) {
        rt = ++tot;
    }

    sum[rt] += val;
    if (l == r) {
        return;
    }

    int m = (l + r) / 2;
    if (pos <= m) {
        upd(ls[rt], l, m, pos, val);
    } else {
        upd(rs[rt], m + 1, r, pos, val);
    }
}

ll query_inner(int rt, int l, int r, int ql, int qr) {
    if (ql > r || qr < l || !rt) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return sum[rt];
    }

    int m = (l + r) / 2;
    return query_inner(ls[rt], l, m, ql, qr) + query_inner(rs[rt], m + 1, r, ql, qr);
}

ll query_prefix(int pos, int val_l, int val_r) {
    ll res = 0;
    for (int i = pos; i > 0; i -= lb(i)) {
        res += query_inner(root[i], 1, n, val_l, val_r);
    }
    return res;
}

ll query(int pos_l, int pos_r, int val_l, int val_r) {
    if (pos_l > pos_r || val_l > val_r) {
        return 0;
    }
    return query_prefix(pos_r, val_l, val_r) - query_prefix(pos_l - 1, val_l, val_r);
}
int Multitest = 0;

void init() {}

void solve() {
    rd(n, m);

    tot = 0;
    ll ans = 0;
    F(i, 1, n) {
        rd(a[i]);
        pos[a[i]] = i;
        ans += query(1, i - 1, a[i] + 1, n);
        for (int j = i; j <= n; j += lb(j)) {
            upd(root[j], 1, n, a[i], 1);
        }
    }

    F(i, 1, m) {
        prt(ans);
        int val_to_del;
        rd(val_to_del);
        int p = pos[val_to_del];
        ll lost_left = query(1, p - 1, val_to_del + 1, n);
        ll lost_right = query(p + 1, n, 1, val_to_del - 1);
        ans -= (lost_left + lost_right);
        for (int j = p; j <= n; j += lb(j)) {
            upd(root[j], 1, n, val_to_del, -1);
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
