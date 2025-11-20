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

constexpr int N = 3e3 + 5;

int grid[N][N];
ll dp[N][N];
int best1[N][N];
int best2[N][N];

int Multitest = 0;

void init() {}

void solve() {
    int h, w, k;
    rd(h, w, k);

    F(i, 1, h) {
        F(j, 1, w) { grid[i][j] = 0; }
    }

    F(i, 1, k) {
        int r, c;
        rd(r, c);
        grid[r][c] = 1;
    }

    F(i, 1, h) {
        F(j, 1, w) {
            dp[i][j] = -1;
            best1[i][j] = inf;
            best2[i][j] = inf;
        }
    }

    struct Node {
        int d;
        int x;
        int y;
        bool operator>(const Node &other) const { return d > other.d; }
    };

    priority_queue<Node, vector<Node>, greater<>> pq;

    F(i, 1, h) {
        F(j, 1, w) {
            if (grid[i][j]) {
                dp[i][j] = 0;
                pq.push({0, i, j});
            }
        }
    }

    auto push_neighbor = [&](int ux, int uy, int val) {
        if (val <= best1[ux][uy]) {
            best2[ux][uy] = best1[ux][uy];
            best1[ux][uy] = val;
        } else if (val < best2[ux][uy]) {
            best2[ux][uy] = val;
        }
        if (dp[ux][uy] == -1 && !grid[ux][uy] && best2[ux][uy] < inf) {
            dp[ux][uy] = (ll) best2[ux][uy] + 1;
            pq.push({(int) dp[ux][uy], ux, uy});
        }
    };

    auto add = [&](int x, int y, int dcur) {
        static const int dx[4] = {-1, 1, 0, 0};
        static const int dy[4] = {0, 0, -1, 1};
        F(kd, 0, 3) {
            int nx = x + dx[kd];
            int ny = y + dy[kd];
            if (nx >= 1 && nx <= h && ny >= 1 && ny <= w) {
                push_neighbor(nx, ny, dcur);
            }
        }
    };

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();
        if (dp[cur.x][cur.y] != cur.d) {
            continue;
        }
        add(cur.x, cur.y, cur.d);
    }

    ll ans = 0;
    F(i, 1, h) {
        F(j, 1, w) {
            if (dp[i][j] != -1) {
                ans += dp[i][j];
            }
        }
    }

    prt(ans);
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
