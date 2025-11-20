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

void solve() {
    int n, m;
    rd(n, m);

    vvi g(n + 1);
    F(i, 1, m) {
        int u, v;
        rd(u, v);
        g[u].pb(v);
        g[v].pb(u);
    }

    vi dis1(n + 1, inf), dis2(n + 1, inf);
    vi r1(n + 1, -1), r2(n + 1, -1);
    string s;
    rd(s);
    struct State {
        int u, root, d;
    };
    queue<State> q;
    F(i, 1, n) {
        if (s[i - 1] == 'S') {
            dis1[i] = 0;
            r1[i] = i;
            q.push({i, i, 0});
        }
    }

    auto push_candidate = [&](int v, int root, int nd) {
        if (r1[v] == root) {
            if (nd < dis1[v]) {
                dis1[v] = nd;
                q.push({v, root, nd});
            }
            return;
        }
        if (r2[v] == root) {
            if (nd < dis2[v]) {
                dis2[v] = nd;
                q.push({v, root, nd});
            }
            return;
        }
        if (nd < dis1[v]) {
            r2[v] = r1[v];
            dis2[v] = dis1[v];
            r1[v] = root;
            dis1[v] = nd;
            q.push({v, root, nd});
        } else if (nd < dis2[v]) {
            r2[v] = root;
            dis2[v] = nd;
            q.push({v, root, nd});
        }
    };

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int u = cur.u, root = cur.root, d = cur.d;
        if (!((r1[u] == root && dis1[u] == d) || (r2[u] == root && dis2[u] == d)))
            continue;
        for (int v: g[u]) {
            int nd = d + 1;
            push_candidate(v, root, nd);
        }
    }

    F(i, 1, n) {
        if (s[i - 1] == 'D') {
            prt(dis1[i] + dis2[i]);
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
