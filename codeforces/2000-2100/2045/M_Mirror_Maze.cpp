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

int r, c;
vector<vector<int>> grid;

int total = 0;

bool dfs(int sx, int sy, int dir) {
    vector<vector<array<bool, 4>>> vis(r, vector<array<bool, 4>>(c, {false, false, false, false}));
    vector<vector<bool>> hit(r, vector<bool>(c, false));
    int count = 0;

    int x = sx, y = sy, d = dir;
    while (true) {
        if (x < 0 || x >= r || y < 0 || y >= c)
            break;
        if (vis[x][y][d])
            break; // loop
        vis[x][y][d] = true;

        if (grid[x][y] != 0 && !hit[x][y]) {
            hit[x][y] = true;
            count++;
        }

        if (grid[x][y] == 0) {
            if (d == 0)
                y++;
            else if (d == 1)
                x++;
            else if (d == 2)
                y--;
            else
                x--;
        } else if (grid[x][y] == 1) {
            if (d == 0) {
                d = 3;
                x--;
            } else if (d == 1) {
                d = 2;
                y--;
            } else if (d == 2) {
                d = 1;
                x++;
            } else {
                d = 0;
                y++;
            }
        } else { // '\'
            if (d == 0) {
                d = 1;
                x++;
            } else if (d == 1) {
                d = 0;
                y++;
            } else if (d == 2) {
                d = 3;
                x--;
            } else {
                d = 2;
                y--;
            }
        }
    }
    return count == total;
}

void solve() {
    cin >> r >> c;
    grid.assign(r, vector<int>(c, 0));
    For(i, r) {
        string s;
        cin >> s;
        For(j, c) {
            if (s[j] == '/')
                grid[i][j] = 1, total++;
            else if (s[j] == '\\')
                grid[i][j] = 2, total++;
        }
    }

    vector<string> ans;

    For(j, c) if (dfs(0, j, 1)) ans.emplace_back("N" + to_string(j + 1));
    For(j, c) if (dfs(r - 1, j, 3)) ans.emplace_back("S" + to_string(j + 1));
    For(i, r) if (dfs(i, 0, 0)) ans.emplace_back("W" + to_string(i + 1));
    For(i, r) if (dfs(i, c - 1, 2)) ans.emplace_back("E" + to_string(i + 1));

    cout << ans.size() << '\n';
    for (auto &s: ans)
        cout << s << ' ';
    cout << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
