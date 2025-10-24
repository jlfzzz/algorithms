#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define ld long double
#define db double
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<ll, ll>;
#define ull unsigned long long
constexpr int MOD = int(1e9 + 7);
constexpr int MOD2 = int(998244353);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

namespace utils {
    void debug() { cerr << "\n"; }

    template<typename T, typename... Args>
    void debug(const string &s, T x, Args... args) {
        cerr << s << " = " << x;
        if (sizeof...(args) > 0)
            cerr << ", ";
        debug(args...);
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
    void prt_vec(const vector<T> &v) {
        for (size_t i = 0; i < v.size(); i++) {
            if (i)
                cout << " ";
            cout << v[i];
        }
        cout << "\n";
    }

    template<typename T>
    void prt_vec(const vector<T> &v, int start_index) {
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
    void rd_vec(vector<T> &v) {
        for (auto &x: v) {
            rd(x);
        }
    }

    template<typename T>
    void rd_vec(vector<T> &v, int start_index) {
        for (int i = start_index; i < (int) v.size(); i++) {
            rd(v[i]);
        }
    }

    struct range : ranges::view_base {
        struct Iterator {
            using iterator_category = random_access_iterator_tag;
            using value_type = long long;
            using difference_type = ptrdiff_t;
            ll val, d;
            Iterator() = default;
            Iterator(ll val, ll d) : val(val), d(d) {};
            value_type operator*() const { return val; }
            Iterator &operator++() { return val += d, *this; }
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }
            Iterator &operator--() { return val -= d, *this; }
            Iterator operator--(int) {
                Iterator tmp = *this;
                --(*this);
                return tmp;
            }
            difference_type operator-(const Iterator &other) const { return (val - other.val) / d; }
            bool operator==(const Iterator &other) const { return val == other.val; }
        };
        Iterator Begin, End;
        explicit range(ll n) : Begin(0, 1), End(max(n, ll{0}), 1) {};
        range(ll a, ll b, ll d = ll(1)) : Begin(a, d), End(b, d) {
            ll cnt = b == a or (b - a > 0) != (d > 0) ? 0 : (b - a) / d + bool((b - a) % d);
            End.val = a + max(cnt, ll(0)) * d;
        };
        [[nodiscard]] Iterator begin() const { return Begin; }
        [[nodiscard]] Iterator end() const { return End; };
        [[nodiscard]] ptrdiff_t size() const { return End - Begin; }
    };
} // namespace utils

using namespace utils;

#define int ll

int Multitest = 0;

void init() {}

// 1 dfs找环。每个环上的子树求树形dp直径，维护最大直径和最大经过这个点往下的两个。
// 2 枚举环上点，删这个点和它下一个点之间的边。假设顺时针，先预处理逆时针的每个点到这个第一个点的
// 就是逆时针前缀和，就是环上边前缀和，加子树max。枚举顺时针，还是子树max，先减掉枚举顺时针的前缀和
// 然后加入map，map里面每个偏移量就是当前这个点到起点的前缀和
// 3 删子树的，就是树形dp。

void solve() {
    int n;
    rd(n);

    vector<vector<pii>> g(n + 1);
    for (int i = 0; i < n; i++) {
        int u, v, w;
        rd(u, v, w);
        g[u].eb(v, w);
        g[v].eb(u, w);
    }

    vector<int> circle, on(n + 1);

    {
        vector<int> vis(n + 1), parent(n + 1);
        bool find = false;
        auto dfs = [&](this auto &&dfs, int u, int fa) -> void {
            if (find) {
                return;
            }
            vis[u] = 1;
            for (auto [v, w]: g[u]) {
                if (v == fa) {
                    continue;
                }
                if (!vis[v]) {
                    parent[v] = u;
                    dfs(v, u);
                    if (find) {
                        return;
                    }
                } else {
                    int t = u;
                    while (t != v) {
                        circle.pb(t);
                        t = parent[t];
                    }
                    circle.pb(t);
                    reverse(circle.begin(), circle.end());
                    find = true;
                    return;
                }
            }
        };

        dfs(1, 0);
    }

    for (int x: circle) {
        on[x] = 1;
    }

    map<pii, int> dis;
    int sz = circle.size();
    for (int i = 0; i < sz; i++) {
        int u = circle[i];
        int v = circle[(i + 1) % sz];

        int d = -1;
        for (auto [y, w]: g[u]) {
            if (y == v) {
                d = w;
                break;
            }
        }
        assert(d != -1);

        dis[{u, v}] = d;
        dis[{v, u}] = d;
    }

    vector<int> circleMax(n + 1), dia(n + 1);
    int mxD = 0;
    int ans = inf;
    for (int root: circle) {
        int mx_d = 0;
        function<int(int, int)> dfs2 = [&](int u, int fa) -> int {
            int mx1 = 0, mx2 = 0;
            for (auto [v, w]: g[u]) {
                if (v == fa || on[v]) {
                    continue;
                }
                int t = dfs2(v, u) + w;
                if (t > mx1) {
                    mx2 = mx1;
                    mx1 = t;
                } else if (t > mx2) {
                    mx2 = t;
                }
            }
            mx_d = max(mx_d, mx1 + mx2);
            return mx1;
        };
        circleMax[root] = dfs2(root, 0);
        dia[root] = mx_d;
        mxD = max(mxD, mx_d);
    }

    {
        // 使用前后缀 DP 按答案代码思路实现
        int N = sz;
        vector<int> mxd(N + 2), d(N + 2), ew(N + 2);
        for (int i = 1; i <= N; i++) {
            int u = circle[i - 1];
            int v = circle[i % N];
            mxd[i] = circleMax[u];
            d[i] = dia[u];
            ew[i] = dis[{u, v}];
        }
        ew[0] = ew[N];

        vector<int> mxq(N + 2), mxh(N + 3), mx1(N + 2), mx2(N + 3);
        int curDis = 0;
        int mxl = 0;
        for (int i = 1; i <= N; i++) {
            mxq[i] = max(mxq[i - 1], mxd[i] + curDis);
            if (i > 1) {
                mx1[i] = max(mx1[i - 1], mxl + curDis + mxd[i]);
            }
            mxl = max(mxl, mxd[i] - curDis);
            curDis += ew[i];
        }

        curDis = 0;
        mxl = 0;
        int best = mx1[N];
        for (int i = N; i >= 1; i--) {
            mxh[i] = max(mxh[i + 1], mxd[i] + curDis);
            if (i < N) {
                mx2[i] = max(mx2[i + 1], mxl + curDis + mxd[i]);
            }
            mxl = max(mxl, mxd[i] - curDis);
            curDis += ew[i - 1];
        }
        for (int i = N - 1; i >= 1; i--) {
            int cand = max(max(mx1[i], mx2[i + 1]), mxq[i] + mxh[i + 1] + ew[N]);
            best = min(best, cand);
        }
        for (int i = 1; i <= N; i++) {
            best = max(best, d[i]);
        }
        ans = best;
    }
    prt(ans);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    if (Multitest) {
        rd(T);
    }
    while (T--)
        solve();
    return 0;
}
