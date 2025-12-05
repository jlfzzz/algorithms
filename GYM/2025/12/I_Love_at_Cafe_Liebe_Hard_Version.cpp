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

constexpr int N = 1e6 + 5;

int Multitest = 1;

void init() {}

void solve() {
    ll n, m, v;
    rd(n, m, v);

    string s;
    rd(s);
    s = '#' + s;

    struct Trade {
        db a;
        int x;
        db b;
        int y;
        db c;
        int z;
    };

    vector<Trade> trades;
    vvi adj(n + 1);

    F(i, 1, m) {
        db a, b, c;
        int x, y, z;
        rd(a, x, b, y, c, z);
        trades.push_back({a, x, b, y, c, z});
        adj[x].pb(i - 1);
        adj[y].pb(i - 1);
    }

    vector<db> dis(n + 1, 1e300);
    vector<bool> vis(n + 1, false);
    vector<int> cnt(n + 1, 0);
    queue<int> q;

    F(i, 1, n) {
        if (s[i] == '1') {
            dis[i] = 1.0;
            if (!vis[i]) {
                vis[i] = true;
                q.push(i);
                cnt[i] = 1;
            }
        }
    }

    auto spfa = [&]() -> bool {
        int limit = 2000000;
        while (!q.empty()) {
            if (limit-- == 0)
                break;

            int u = q.front();
            q.pop();
            vis[u] = false;

            if (dis[1] < 1e-15)
                return false;

            for (int idx: adj[u]) {
                auto &t = trades[idx];
                if (dis[t.x] < 1e299 && dis[t.y] < 1e299) {
                    db new_cost = (t.a * dis[t.x] + t.b * dis[t.y]) / t.c;
                    if (new_cost < dis[t.z] - 1e-15) {
                        dis[t.z] = new_cost;
                        if (!vis[t.z]) {
                            q.push(t.z);
                            vis[t.z] = true;
                        }
                    }
                }
            }
        }
        return true;
    };

    if (!spfa() || dis[1] < 1e-15) {
        cout << -1 << endl;
        return;
    }

    cout << fixed << setprecision(15);
    if (dis[1] > 1e299) {
        cout << 0.0 << endl;
    } else {
        cout << (db) v / dis[1] << endl;
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
