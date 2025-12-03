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

constexpr int N = 2e5 + 5;

int Multitest = 0;

void init() {}

struct Node {
    vi mn;
    Node() : mn(10, 0) {}
} tree[4 * N + 5];

int LIM;
int tin[N], tout[N];
int dfn[N];
int timer;

int need[10];
int have[N][10];
vi g[N];
vi ans;
vi primes;

Node merge(Node &l, Node &r) {
    Node res;
    F(i, 0, LIM) { res.mn[i] = max(l.mn[i], r.mn[i]); }
    return res;
}

void build(int o, int l, int r) {
    if (l == r) {
        int u = dfn[l];
        F(i, 0, LIM) { tree[o].mn[i] = have[u][i]; }
        return;
    }

    int m = (l + r) / 2;
    build(o * 2, l, m);
    build(o * 2 + 1, m + 1, r);
    tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
}

void upd(int o, int l, int r, int ql, int qr, const vp &val, int cur_year) {
    if (l > qr || r < ql) {
        return;
    }

    if (l >= ql && r <= qr) {
        bool done = true;
        for (auto [id, cnt]: val) {
            if (tree[o].mn[id] > 0) {
                done = false;
                break;
            }
        }
        if (done) {
            return;
        }
    }

    if (l == r) {
        int u = dfn[l];

        for (auto [id, cnt]: val) {
            tree[o].mn[id] -= cnt;
        }

        if (ans[u] == -1) {
            bool ok = true;
            F(i, 0, LIM) {
                if (tree[o].mn[i] > 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                ans[u] = cur_year;
                F(i, 0, LIM) tree[o].mn[i] = 0;
            }
        }

        return;
    }

    int m = (l + r) / 2;
    upd(o * 2, l, m, ql, qr, val, cur_year);
    upd(o * 2 + 1, m + 1, r, ql, qr, val, cur_year);
    tree[o] = merge(tree[o * 2], tree[o * 2 + 1]);
}

void dfs(int u) {
    tin[u] = ++timer;
    dfn[tin[u]] = u;
    for (int v: g[u]) {
        dfs(v);
    }
    tout[u] = timer;
}

void solve() {
    int n, q;
    int k;
    rd(n, k, q);

    vl a(n + 1);
    rv(a, 1);

    F(i, 1, n) g[i].clear();
    F(i, 2, n) {
        int p;
        rd(p);
        g[p].pb(i);
    }

    if (k == 1) {
        F(i, 1, q) {
            int u;
            ll x;
            rd(u, x);
        }
        F(i, 1, n) { cout << 0 << (i == n ? '\n' : ' '); }
        return;
    }

    primes.clear();
    int tmpk = k;
    F(i, 2, (int) sqrt(tmpk) + 1) {
        if (tmpk % i == 0) {
            int c = 0;
            while (tmpk % i == 0) {
                tmpk /= i;
                c++;
            }
            primes.pb(i);
            need[primes.size() - 1] = c;
        }
    }
    if (tmpk > 1) {
        primes.pb(tmpk);
        need[primes.size() - 1] = 1;
    }

    int pcnt = (int) primes.size();
    LIM = pcnt - 1;

    timer = 0;
    dfs(1);

    F(u, 1, n) {
        ll x = a[u];
        F(i, 0, pcnt - 1) {
            int p = primes[i];
            int c = 0;
            while (x % p == 0) {
                x /= p;
                c++;
            }
            have[u][i] = max(0, need[i] - c);
        }
    }

    ans.assign(n + 1, -1);
    F(u, 1, n) {
        bool happy = true;
        F(i, 0, pcnt - 1) {
            if (have[u][i] > 0) {
                happy = false;
                break;
            }
        }
        if (happy)
            ans[u] = 0;
    }

    build(1, 1, n);

    F(yr, 1, q) {
        int u;
        ll x;
        rd(u, x);

        vp val;
        F(i, 0, pcnt - 1) {
            if (x == 1)
                break;
            int p = primes[i];
            if (x % p == 0) {
                int c = 0;
                while (x % p == 0) {
                    x /= p;
                    c++;
                }
                if (c > 0)
                    val.pb(i, c);
            }
        }
        if (val.empty())
            continue;

        upd(1, 1, n, tin[u], tout[u], val, yr);
    }

    F(i, 1, n) { cout << ans[i] << (i == n ? '\n' : ' '); }
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
