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

struct node {
    int x, y, d, f;

    bool operator<(const node &other) const { return d > other.d; }
};


void solve() {
    int h, w;
    cin >> h >> w;

    vector<vector<char>> grid(h, vector<char>(w));

    pii start;
    pii goal;

    For(i, h) {
        For(j, w) {
            char c;
            cin >> c;
            grid[i][j] = c;
            if (c == 'S') {
                start = {i, j};
            } else if (c == 'G') {
                goal = {i, j};
            }
        }
    }

    priority_queue<node> pq;
    pq.emplace(start.first, start.second, 0, 0);
    vector<vector<vector<int>>> dis(h, vector<vector<int>>(w, {inf, inf}));
    dis[start.first][start.second][0] = 0;
    while (!pq.empty()) {
        auto [x, y, d, f] = pq.top();
        pq.pop();

        if (x == goal.first && y == goal.second) {
            cout << d << '\n';
            return;
        }

        if (d > dis[x][y][f])
            continue;

        for (auto &[dx, dy]: DIR) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < h && ny >= 0 && ny < w) {
                if (grid[nx][ny] == '#') {
                    continue;
                }

                if (f) {
                    if (grid[nx][ny] == 'o') {
                        continue;
                    }
                } else {
                    if (grid[nx][ny] == 'x') {
                        continue;
                    }
                }



                if (grid[nx][ny] == '?') {
                    if (d + 1 >= dis[nx][ny][!f]) {
                        continue;
                    }
                    dis[nx][ny][!f] = d + 1;
                    pq.emplace(nx, ny, d + 1, !f);
                } else {
                    if (d + 1 >= dis[nx][ny][f]) {
                        continue;
                    }
                    dis[nx][ny][f] = d + 1;
                    pq.emplace(nx, ny, d + 1, f);
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
