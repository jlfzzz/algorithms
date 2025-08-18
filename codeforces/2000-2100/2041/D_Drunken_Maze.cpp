#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

int DIR[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    // dis[i][j][k] k = dir*4 + cnt, dir∈[0,3], cnt∈[1,3]
    vector dis(n, vector<vector<int>>(m, vector<int>(16, inf)));

    pii start{0, 0};
    pii end{0, 0};

    For(i, n) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '.') {
                grid[i][j] = 1;
            } else if (s[j] == 'S') {
                grid[i][j] = 1;
                start = {i, j};
            } else if (s[j] == 'T') {
                grid[i][j] = 1;
                end = {i, j};
            }
        }
    }

    struct info {
        int d, i, j, pre_dir, pre_cnt;
    };

    auto cmp = [](info &a, info &b) -> bool { return a.d > b.d; };
    priority_queue<info, vector<info>, decltype(cmp)> pq(cmp);

    // 初始状态：从起点开始，向四个方向走第一步
    For(dir, 4) {
        int dx = DIR[dir][0], dy = DIR[dir][1];
        int x = start.first + dx, y = start.second + dy;
        if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != 0) {
            int mask = dir * 4 + 1; // 方向dir，走了1步
            dis[x][y][mask] = 1;
            pq.emplace(1, x, y, dir, 1);
        }
    }

    while (!pq.empty()) {
        auto [d, i, j, pre_dir, pre_cnt] = pq.top();
        pq.pop();

        if (i == end.first && j == end.second) {
            cout << d << '\n';
            return;
        }

        int curr_mask = pre_dir * 4 + pre_cnt;
        if (d > dis[i][j][curr_mask]) {
            continue;
        }

        For(dir, 4) {
            int dx = DIR[dir][0], dy = DIR[dir][1];
            int x = i + dx, y = j + dy;
            if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != 0) {
                if (dir == pre_dir) {
                    // 继续同方向
                    if (pre_cnt < 3) {
                        int nxt_d = d + 1;
                        int mask = dir * 4 + pre_cnt + 1;
                        if (nxt_d < dis[x][y][mask]) {
                            dis[x][y][mask] = nxt_d;
                            pq.emplace(nxt_d, x, y, pre_dir, pre_cnt + 1);
                        }
                    } else {
                        // 已经走了3步，需要重置
                        int nxt_d = d + 3;
                        int mask = dir * 4 + 2; // 重置后相当于走了2步
                        if (nxt_d < dis[x][y][mask]) {
                            dis[x][y][mask] = nxt_d;
                            pq.emplace(nxt_d, x, y, pre_dir, 2);
                        }
                    }
                } else {
                    // 改变方向
                    int nxt_d = d + 1;
                    int mask = dir * 4 + 1;
                    if (nxt_d < dis[x][y][mask]) {
                        dis[x][y][mask] = nxt_d;
                        pq.emplace(nxt_d, x, y, dir, 1);
                    }
                }
            }
        }
    }

    cout << -1 << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}