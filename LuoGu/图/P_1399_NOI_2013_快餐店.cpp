#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define pb push_back
#define pf push_front
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
using pii = pair<int, int>;
using pll = pair<ll, ll>;
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

void solve() {
    int n;
    cin >> n;

    vector<vector<pair<int, double>>> g(n + 1);
    for (int i = 0; i < n; ++i) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<pair<int, double>> parent(n + 1, {-1, 0});
    vector<int> color(n + 1, 0);
    vector<int> cycle;
    double cycleLen = 0;
    bool found = false;

    auto dfs = [&](auto &&dfs, int u, int fa) -> void {
        if (found)
            return;
        color[u] = 1;
        for (auto &[v, w]: g[u]) {
            if (v == fa)
                continue;
            if (!color[v]) {
                parent[v] = {u, w};
                dfs(dfs, v, u);
                if (found)
                    return;
            } else if (color[v] == 1) {
                found = true;
                cycle.push_back(v);
                cycleLen += w;
                int x = u;
                while (x != v) {
                    cycle.push_back(x);
                    cycleLen += parent[x].second;
                    x = parent[x].first;
                }
                reverse(cycle.begin(), cycle.end());
                return;
            }
        }
        color[u] = 2;
    };

    dfs(dfs, 1, -1);

    int m = cycle.size();
    vector<int> onCycle(n + 1, 0);
    for (int x: cycle)
        onCycle[x] = 1;

    // 计算每个环节点挂树的最大深度和子树直径半径
    vector<double> dep_on_cycle(m, 0.0);
    vector<double> radius_on_cycle(m, 0.0);
    for (int i = 0; i < m; ++i) {
        int root_u = cycle[i];
        double best_dia = 0.0;
        auto dfs_metrics = [&](auto &&dfs_metrics, int u, int fa) -> double {
            double top1 = 0.0, top2 = 0.0;
            for (auto &[v, w]: g[u]) {
                if (v == fa)
                    continue;
                if (onCycle[v] && v != root_u)
                    continue; // 不跨到其他环点
                double d = w + dfs_metrics(dfs_metrics, v, u);
                if (d >= top1) {
                    top2 = top1;
                    top1 = d;
                } else if (d > top2) {
                    top2 = d;
                }
            }
            best_dia = max(best_dia, top1 + top2);
            return top1;
        };
        dep_on_cycle[i] = dfs_metrics(dfs_metrics, root_u, -1);
        radius_on_cycle[i] = best_dia / 2.0;
    }

    // 构造环上相邻边权（按 cycle 的顺序）与总环长
    vector<double> edge_w(m, 0.0);
    for (int i = 0; i < m; ++i) {
        int a = cycle[i];
        int b = cycle[(i + 1) % m];
        double w = 0.0;
        for (auto &[v, ww]: g[a])
            if (v == b) {
                w = ww;
                break;
            }
        edge_w[i] = w;
    }
    double L = 0.0;
    for (double w: edge_w)
        L += w;

    // 构造位置数组（前缀距离），以及双倍展开
    vector<double> pos(2 * m, 0.0);
    for (int i = 1; i <= m; ++i)
        pos[i] = pos[i - 1] + edge_w[i - 1];
    for (int i = 0; i < m; ++i)
        pos[i + m] = pos[i] + L;

    vector<double> dep2(2 * m, 0.0);
    for (int i = 0; i < 2 * m; ++i)
        dep2[i] = dep_on_cycle[i % m];

    // 计算长度为 m 的滑动窗口最大值：val1 = dep + pos，val2 = dep - pos
    auto sliding_max = [&](const vector<double> &arr, int k) {
        int N = (int) arr.size();
        vector<double> res(max(0LL, (ll) N - (ll) k + 1), 0.0);
        deque<int> dq;
        for (int i = 0; i < N; ++i) {
            while (!dq.empty() && arr[dq.back()] <= arr[i])
                dq.pop_back();
            dq.push_back(i);
            if (!dq.empty() && dq.front() <= i - k)
                dq.pop_front();
            if (i >= k - 1)
                res[i - (k - 1)] = arr[dq.front()];
        }
        return res;
    };

    vector<double> val1(2 * m), val2(2 * m);
    for (int i = 0; i < 2 * m; ++i) {
        val1[i] = dep2[i] + pos[i];
        val2[i] = dep2[i] - pos[i];
    }
    auto max1 = sliding_max(val1, m);
    auto max2 = sliding_max(val2, m);

    // 在所有长度为 m 的窗口中取 (max1 + max2) / 2 的最小值（只在环上）
    double ans_cycle = 1e300;
    for (int i = 0; i < m; ++i) {
        ans_cycle = min(ans_cycle, (max1[i] + max2[i]) / 2.0);
    }

    // 进一步考虑“进入子树”的优化：对每个环点 i，求外部最大值 B_i
    vector<double> A1(2 * m), A2(2 * m);
    for (int i = 0; i < 2 * m; ++i) {
        A1[i] = dep2[i] + pos[i];
        A2[i] = dep2[i] - pos[i];
    }

    int j = 0;
    deque<int> dq1, dq2; // dq1 维护区间 (i, j] 上 A1 的最大，dq2 维护区间 (j, i+m-1] 上 A2 的最大

    auto push_dq_max = [&](deque<int> &dq, const vector<double> &arr, int idx) {
        while (!dq.empty() && arr[dq.back()] <= arr[idx])
            dq.pop_back();
        dq.push_back(idx);
    };

    // 初始化 i=0
    while (j + 1 <= m - 1 && pos[j + 1] - pos[0] <= L / 2.0) {
        ++j;
        push_dq_max(dq1, A1, j);
    }
    for (int k = j + 1; k <= m - 1; ++k)
        push_dq_max(dq2, A2, k);

    double ans_with_branch = 1e300;
    for (int i = 0; i < m; ++i) {
        // 计算 B_i
        while (!dq1.empty() && dq1.front() <= i)
            dq1.pop_front();
        while (!dq2.empty() && dq2.front() <= j)
            dq2.pop_front();

        double part1 = dq1.empty() ? -1e300 : (A1[dq1.front()] - pos[i]);
        double part2 = dq2.empty() ? -1e300 : (A2[dq2.front()] + pos[i] + L);
        double B = max(part1, part2);

        double A = dep_on_cycle[i];
        double R = radius_on_cycle[i];

        double cand = max(B, A); // x = 0
        if (A >= B)
            cand = min(cand, max(R, (A + B) / 2.0));
        ans_with_branch = min(ans_with_branch, cand);

        // 移动到 i+1，更新窗口
        int next_i = i + 1;
        // 扩张 j，使 pos[j+1]-pos[next_i] <= L/2
        while (j + 1 <= next_i + m - 1 && pos[j + 1] - pos[next_i] <= L / 2.0) {
            ++j;
            push_dq_max(dq1, A1, j);
        }
        // dq2 窗口右端增加一个新元素 r = next_i + m - 1
        int r = next_i + m - 1;
        if (r < 2 * m)
            push_dq_max(dq2, A2, r);
    }

    double ans = min(ans_cycle, ans_with_branch);
    cout.setf(std::ios::fixed);
    cout << setprecision(1) << ans << '\n';
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
