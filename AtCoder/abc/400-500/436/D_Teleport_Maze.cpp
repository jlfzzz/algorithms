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

int dir[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

void init() {}

void solve() {
    int h, w;
    rd(h, w);

    vector<string> grid(h);
    rv(grid);

    // 预处理所有字母的位置
    vvp pos(26);
    F(i, 0, h - 1) {
        F(j, 0, w - 1) {
            if (islower(grid[i][j])) {
                pos[grid[i][j] - 'a'].pb(i, j);
            }
        }
    }

    // dis 初始化为 -1 代表未访问
    vvi dis(h, vi(w, -1));
    queue<pii> q;

    // 起点
    dis[0][0] = 0;
    q.push({0, 0});

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        int d = dis[r][c];

        // 终点判断（可选，BFS第一次到达即最短）
        if (r == h - 1 && c == w - 1) {
            prt(d);
            return;
        }

        // 1. 普通移动 (Walk)
        for (auto &dr: dir) {
            int nr = r + dr[0];
            int nc = c + dr[1];

            if (nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] != '#' && dis[nr][nc] == -1) {
                dis[nr][nc] = d + 1;
                q.push({nr, nc});
            }
        }

        // 2. 传送移动 (Warp)
        // 只有当前格子是字母，且该字母未被“展开”过时才处理
        if (islower(grid[r][c])) {
            int idx = grid[r][c] - 'a';

            // 核心优化：如果 pos[idx] 不为空，说明这是第一次通过传送到达该类字母
            if (!pos[idx].empty()) {
                for (auto [nr, nc]: pos[idx]) {
                    // 传送也是 1 步操作
                    if (dis[nr][nc] == -1) {
                        dis[nr][nc] = d + 1;
                        q.push({nr, nc});
                    }
                }
                // 关键：清空列表！
                // 以后再遇到这个字母，就不需要再把它的同伴加入队列了
                pos[idx].clear();
            }
        }
    }

    prt(-1);
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
