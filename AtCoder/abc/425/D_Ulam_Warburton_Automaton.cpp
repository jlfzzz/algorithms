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
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

int DIR[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

void solve() {
    int h, w;
    cin >> h >> w;
    vector<vector<int>> grid(h, vector<int>(w));
    For(i, h) {
        For(j, w) {
            char c;
            cin >> c;
            if (c == '.') {
                grid[i][j] = 1;
            }
        }
    }

    vector<vector<int>> deg(h, vector<int>(w, 0));
    For(i, h) {
        For(j, w) {
            int cnt = 0;
            for (auto &[dx, dy]: DIR) {
                int ni = i + dx, nj = j + dy;
                if (ni >= 0 && ni < h && nj >= 0 && nj < w) {
                    if (!grid[ni][nj])
                        cnt++;
                }
            }
            deg[i][j] = cnt;
        }
    }

    vector<pii> cur;
    For(i, h) {
        For(j, w) {
            if (grid[i][j] && deg[i][j] == 1)
                cur.emplace_back(i, j);
        }
    }

    while (!cur.empty()) {
        map<int, int> add;

        for (auto &[x, y]: cur) {
            for (auto &[dx, dy]: DIR) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < h && ny >= 0 && ny < w) {
                    if (grid[nx][ny]) {
                        int id = nx * w + ny;
                        add[id] += 1;
                    }
                }
            }
        }

        for (auto &[x, y]: cur) {
            grid[x][y] = 0;
        }

        vector<pii> nxt;
        for (auto &kv: add) {
            int id = kv.first;
            int cnt = kv.second;
            int i = id / w;
            int j = id % w;
            if (grid[i][j]) {
                if (deg[i][j] + cnt == 1) {
                    nxt.emplace_back(i, j);
                }
                deg[i][j] += cnt;
            }
        }

        cur.swap(nxt);
    }

    int ans = 0;
    For(i, h) {
        For(j, w) {
            if (!grid[i][j]) {
                ans++;
            }
        }
    }

    cout << ans << '\n';
}



signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
