#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

template<typename T>
using ordered_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, std::less<T>, __gnu_pbds::rb_tree_tag,
                                     __gnu_pbds::tree_order_statistics_node_update>;

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

constexpr int N = 1e5 + 5;

int Multitest = 0;

constexpr int M = 40 * N;

int ls[M], rs[M], tree[M], root[N];
int tot;

int build(int l, int r, vi &v) {
    int cur = ++tot;
    if (l == r) {
        tree[cur] = v[l];
        return cur;
    }

    int m = (l + r) / 2;
    ls[cur] = build(l, m, v);
    rs[cur] = build(m + 1, r, v);
    return cur;
}

int update(int pre, int l, int r, int pos, int val) {
    int cur = ++tot;
    tree[cur] = tree[pre];
    ls[cur] = ls[pre];
    rs[cur] = rs[pre];

    if (l == r) {
        tree[cur] += val;
        return cur;
    }
    int m = (l + r) / 2;
    if (pos <= m) {
        ls[cur] = update(ls[pre], l, m, pos, val);
    } else {
        rs[cur] = update(rs[pre], m + 1, r, pos, val);
    }
    return cur;
}

int query(int pre, int cur, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) {
        return 0;
    }

    if (l >= ql && r <= qr) {
        return tree[cur] - tree[pre];
    }

    int m = (l + r) / 2;
    return query(ls[pre], ls[cur], l, m, ql, qr) + query(rs[pre], rs[cur], m + 1, r, ql, qr);
}

void init() {}

void solve() {
    int n, m;
    rd(n, m);

    vector<ll> cur(n + 1);
    rv(cur, 1);

    unordered_map<ll, ordered_set<int>> pos;
    pos.reserve(n * 2 + 7);
    for (int i = 1; i <= n; i++) {
        pos[cur[i]].insert(i);
    }

    for (int i = 0; i < m; i++) {
        char op;
        rd(op);
        if (op == 'Q') {
            int A, B;
            ll K;
            rd(A, B, K);
            if (A > B)
                swap(A, B);
            auto it = pos.find(K);
            if (it == pos.end()) {
                cout << 0 << '\n';
            } else {
                auto &s = it->second;
                int ans = (int) s.order_of_key(B + 1) - (int) s.order_of_key(A);
                cout << ans << '\n';
            }
        } else if (op == 'C') {
            int A;
            ll P;
            rd(A, P);
            ll old = cur[A];
            if (old == P)
                continue;
            auto it_old = pos.find(old);
            if (it_old != pos.end()) {
                it_old->second.erase(A);
                if (it_old->second.empty())
                    pos.erase(it_old);
            }
            pos[P].insert(A);
            cur[A] = P;
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
