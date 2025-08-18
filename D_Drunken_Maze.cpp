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

int DIR[4][3] = {{-1, 0, 1}, {0, 1, 2}, {1, 0, 3}, {0, -1, 4}};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    vector<vector<int>> dis(n, vector<int>(m, inf));

    pii start{0, 0};
    pii end{0, 0};

    For(i, n) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '.') {
                grid[i][j] = 1;
            } else if (s[j] == 'S') {
                start = {i, j};
            } else if (s[j] == 'T') {
                end = {i, j};
            }
        }
    }

    struct info {
        int d, i, j, pre_dir, pre_cnt;
    };

    auto cmp = [](info &a, info &b) -> bool { return a.d > b.d; };

    dis[start.first][start.second] = 0;
    priority_queue<info, vector<info>, decltype(cmp)> pq(cmp);

    pq.emplace(0, start.first, start.second, -1, -1);
    while (!pq.empty()) {
        auto [d, i, j, pre_dir, pre_cnt] = pq.top();
        pq.pop();

        if (i == end.first && j == end.second) {
            cout << d << '\n';
            return;
        }

        if (d > dis[i][j]) {
            continue;
        }

        for (auto &[dx, dy, dir]: DIR) {
            int x = i + dx, y = j + dy;
            if (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != 0) {
                if (dir == pre_dir) {
                    if (pre_cnt < 3) {
                        int nxt_d = d + 1;
                        if (nxt_d < dis[x][y]) {
                            dis[x][y] = nxt_d;
                            pq.emplace(nxt_d, x, y, pre_dir, pre_cnt + 1);
                        }
                    } else {
                        int nxt_d = d + 3;
                        if (nxt_d < dis[x][y]) {
                            dis[x][y] = nxt_d;
                            pq.emplace(nxt_d, x, y, pre_dir, 1);
                        }
                    }
                } else {
                    int nxt_d = d + 1;
                    if (nxt_d < dis[x][y]) {
                        dis[x][y] = nxt_d;
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
