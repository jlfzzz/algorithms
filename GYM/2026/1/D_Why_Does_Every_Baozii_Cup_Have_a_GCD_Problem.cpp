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

int Multitest = 0;

void init() {}

int n, q;
int a[100'005];

const int MAXV = 1e7;
const int MAXLCM = 1e7 + 7;

int calc(int a, int b) {
    if (a == MAXLCM || b == MAXLCM)
        return MAXLCM;
    if (a == 0 || b == 0)
        return b ? b : a;
    ll res = (1LL * a / gcd(a, b)) * b;
    if (res > MAXV)
        return MAXLCM;
    return (int) res;
}

struct Node {
    ll sum;
    int lcm;
} tree[400'005];

Node pushup(int l, int r) {
    Node res;
    res.sum = tree[l].sum + tree[r].sum;
    res.lcm = calc(tree[l].lcm, tree[r].lcm);
    return res;
}

void upd(int o, int l, int r, int ql, int qr, int x) {
    if (ql > r || qr < l) {
        return;
    }

    if (ql <= l && r <= qr) {
        if (tree[o].lcm != MAXLCM && x % tree[o].lcm == 0) {
            return;
        }
    }

    if (l == r) {
        tree[o].lcm = gcd(tree[o].lcm, x);
        tree[o].sum = tree[o].lcm;
        return;
    }

    int m = (l + r) / 2;
    upd(o * 2, l, m, ql, qr, x);
    upd(o * 2 + 1, m + 1, r, ql, qr, x);

    tree[o] = pushup(o * 2, o * 2 + 1);
}

void upd2(int o, int l, int r, int i, int x) {
    if (l == r) {
        tree[o].lcm = x;
        tree[o].sum = x;
        return;
    }

    int m = (l + r) / 2;
    if (i <= m) {
        upd2(o * 2, l, m, i, x);
    } else {
        upd2(o * 2 + 1, m + 1, r, i, x);
    }

    tree[o] = pushup(o * 2, o * 2 + 1);
}

ll query(int o, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) {
        return 0;
    }

    if (ql <= l && r <= qr) {
        return tree[o].sum;
    }

    int m = (l + r) / 2;
    return query(o * 2, l, m, ql, qr) + query(o * 2 + 1, m + 1, r, ql, qr);
}

void solve() {
    rd(n, q);

    F(i, 1, n) {
        int t;
        rd(t);
        upd2(1, 1, n, i, t);
    }

    while (q--) {
        int type;
        rd(type);

        if (type == 1) {
            int i, x;
            rd(i, x);
            upd2(1, 1, n, i, x);
        } else if (type == 2) {
            int l, r, x;
            rd(l, r, x);
            upd(1, 1, n, l, r, x);
        } else {
            int l, r;
            rd(l, r);
            prt(query(1, 1, n, l, r));
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
