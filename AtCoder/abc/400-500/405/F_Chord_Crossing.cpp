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

void solve2() {
    int N_in, M;
    rd(N_in, M);
    int max_pos = 2 * N_in;
    vector<pair<int, int>> segs(M);
    vector<int> mark(max_pos + 1, 0);
    for (int i = 0; i < M; i++) {
        int a, b;
        rd(a, b);
        if (a > b) {
            swap(a, b);
        }
        segs[i] = {a, b};
        mark[a] = 1;
        mark[b] = 1;
    }
    vector<int> pref(max_pos + 1, 0);
    for (int i = 1; i <= max_pos; i++) {
        pref[i] = pref[i - 1] + mark[i];
    }
    struct BIT {
        int n;
        vector<int> t;
        void init(int n_) {
            n = n_;
            t.assign(n + 1, 0);
        }
        void add(int i, int v) {
            for (; i <= n; i += i & -i) {
                t[i] += v;
            }
        }
        int sum(int i) {
            int s = 0;
            for (; i > 0; i -= i & -i) {
                s += t[i];
            }
            return s;
        }
        int range(int l, int r) {
            if (l > r) {
                return 0;
            }
            return sum(r) - sum(l - 1);
        }
    } bit;
    bit.init(max_pos + 2);
    sort(all(segs), [](const pair<int, int> &x, const pair<int, int> &y) {
        if (x.second != y.second) {
            return x.second < y.second;
        }
        return x.first < y.first;
    });
    int Q;
    rd(Q);
    struct Query {
        int c, d, id;
    };
    vector<Query> qs(Q);
    for (int i = 0; i < Q; i++) {
        int c, d;
        rd(c, d);
        if (c > d) {
            swap(c, d);
        }
        qs[i] = {c, d, i};
    }
    vector<long long> ans(Q);
    sort(all(qs), [](const Query &x, const Query &y) {
        if (x.d != y.d) {
            return x.d < y.d;
        }
        return x.c < y.c;
    });
    int p = 0;
    for (auto &q: qs) {
        while (p < M && segs[p].second < q.d) {
            bit.add(segs[p].first, 1);
            p++;
        }
        int Ein = pref[q.d - 1] - pref[q.c];
        int Y = bit.range(q.c + 1, q.d - 1);
        ans[q.id] = (long long) Ein - 2LL * (long long) Y;
    }
    for (int i = 0; i < Q; i++) {
        prt(ans[i]);
    }
}

int tot = 0;
int tree[80 * N], ls[80 * N], rs[80 * N];

int upd(int pre, int l, int r, int i, int val) {
    int cur = ++tot;
    ls[cur] = ls[pre];
    rs[cur] = rs[pre];
    tree[cur] = tree[pre] + val;

    if (l == r) {
        return cur;
    }

    int mid = (l + r) >> 1;
    if (i <= mid) {
        ls[cur] = upd(ls[pre], l, mid, i, val);
    } else {
        rs[cur] = upd(rs[pre], mid + 1, r, i, val);
    }

    return cur;
}

int query(int cur, int pre, int l, int r, int ql, int qr) {
    if (!cur && !pre)
        return 0;
    if (ql <= l && r <= qr) {
        return tree[cur] - tree[pre];
    }

    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid)
        res += query(ls[cur], ls[pre], l, mid, ql, qr);
    if (qr > mid)
        res += query(rs[cur], rs[pre], mid + 1, r, ql, qr);
    return res;
}

void solve() {
    int n, m;
    rd(n, m);

    int max_pos = 2 * n;
    vector<vector<int>> byR(max_pos + 1);
    vector<int> mark(max_pos + 1, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        rd(a, b);
        if (a > b) {
            swap(a, b);
        }
        byR[b].push_back(a);
        mark[a] = 1;
        mark[b] = 1;
    }
    vector<int> pref(max_pos + 1, 0);
    for (int i = 1; i <= max_pos; i++) {
        pref[i] = pref[i - 1] + mark[i];
    }

    vi root(max_pos + 1);
    root[0] = 0;
    tot = 0;
    for (int i = 1; i <= max_pos; i++) {
        int cur = root[i - 1];
        for (int a: byR[i]) {
            cur = upd(cur, 1, max_pos, a, 1);
        }
        root[i] = cur;
    }

    int Q;
    rd(Q);
    while (Q--) {
        int c, d;
        rd(c, d);
        if (c > d) {
            swap(c, d);
        }
        int Ein = pref[d - 1] - pref[c];
        int Y = 0;
        if (c + 1 <= d - 1) {
            Y = query(root[d - 1], root[c], 1, max_pos, c + 1, d - 1);
        }
        long long ans = (long long) Ein - 2LL * (long long) Y;
        prt(ans);
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
