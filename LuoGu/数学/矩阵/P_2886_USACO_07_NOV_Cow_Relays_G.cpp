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

constexpr int N = 205; // 2 * 100 + 一点冗余，其实后面用动态 size 就无所谓了

using Matrix = vector<vector<int>>;

Matrix mat_mul(const Matrix &a, const Matrix &b) {
    int sz = (int) a.size();
    Matrix res(sz, vi(sz, inf));

    F(i, 0, sz - 1) {
        F(k, 0, sz - 1) {
            if (a[i][k] == inf)
                continue;
            F(j, 0, sz - 1) {
                if (b[k][j] == inf)
                    continue;
                res[i][j] = min(res[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return res;
}

Matrix ksm(Matrix base, long long e) {
    int sz = (int) base.size();
    Matrix res(sz, vi(sz, inf));
    F(i, 0, sz - 1) res[i][i] = 0;

    while (e) {
        if (e & 1)
            res = mat_mul(res, base);
        base = mat_mul(base, base);
        e >>= 1;
    }
    return res;
}

void solve() {
    int nEdges, t, s, e;
    rd(nEdges, t, s, e);

    map<int, int> id;
    int tot = 0;

    struct Edge {
        int w, u, v;
    };
    vector<Edge> edges;
    edges.reserve(t);

    F(i, 1, t) {
        int w, u, v;
        rd(w, u, v);
        edges.pb(Edge{w, u, v});

        if (!id.contains(u))
            id[u] = tot++;
        if (!id.contains(v))
            id[v] = tot++;
    }

    int V = tot;
    Matrix A(V, vi(V, inf));

    for (auto &ed: edges) {
        int w = ed.w;
        int u = ed.u;
        int v = ed.v;
        int iu = id[u];
        int iv = id[v];
        A[iu][iv] = min(A[iu][iv], w);
        A[iv][iu] = min(A[iv][iu], w);
    }
    Matrix AN = ksm(A, nEdges);

    int sId = id[s];
    int eId = id[e];
    int ans = AN[sId][eId];
    prt(ans);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    while (T--) {
        solve();
    }
}
