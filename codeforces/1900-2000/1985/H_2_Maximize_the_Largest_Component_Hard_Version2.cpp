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
class Uf {
public:
    vector<int> fa;
    vector<int> cnt;
    Uf(int n) : fa(n), cnt(n, 1) {
        for (int i = 0; i < n; i++) {
            fa[i] = i;
        }
    }

    int find(int x) {
        int f = fa[x];
        if (f != x) {
            fa[x] = find(f);
        }
        return fa[x];
    }

    bool merge(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) {
            return false;
        }

        fa[px] = py;
        cnt[py] += cnt[px];
        return true;
    }
};
int DIR[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    For(i, n) {
        string s;
        cin >> s;
        For(j, m) { grid[i][j] = s[j]; }
    }

    auto id = [&](int i, int j) { return i * m + j; };

    Uf uf(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (auto [dx, dy]: DIR) {
                int ni = i + dx, ny = j + dy;
                if (ni >= 0 && ni < n && ny >= 0 && ny < m) {
                    if (grid[i][j] == '#' && grid[ni][ny] == '#')
                        uf.merge(id(i, j), id(ni, ny));
                }
            }
        }
    }

    vector<int> minR(n * m, n), maxR(n * m, -1), minC(n * m, m), maxC(n * m, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '#')
                continue;
            int r = uf.find(id(i, j));
            if (i < minR[r])
                minR[r] = i;
            if (i > maxR[r])
                maxR[r] = i;
            if (j < minC[r])
                minC[r] = j;
            if (j > maxC[r])
                maxC[r] = j;
        }
    }

    vector<int> rowDiff(n + 1, 0), colDiff(m + 1, 0);
    vector<vector<int>> diff(n, vector<int>(m, 0));

    auto add_rect_std = [&](int r1, int c1, int r2, int c2, int val) {
        diff[r1][c1] += val;
        if (r2 + 1 < n)
            diff[r2 + 1][c1] -= val;
        if (c2 + 1 < m)
            diff[r1][c2 + 1] -= val;
        if (r2 + 1 < n && c2 + 1 < m)
            diff[r2 + 1][c2 + 1] += val;
    };

    for (int k = 0; k < n * m; ++k) {
        if (maxR[k] == -1)
            continue;
        int r1 = max(0ll, minR[k] - 1);
        int r2 = min(n - 1, maxR[k] + 1);
        int c1 = max(0ll, minC[k] - 1);
        int c2 = min(m - 1, maxC[k] + 1);
        int val = uf.cnt[k];

        rowDiff[r1] += val;
        rowDiff[r2 + 1 >= n ? n : r2 + 1] -= val;
        colDiff[c1] += val;
        colDiff[c2 + 1 >= m ? m : c2 + 1] -= val;

        add_rect_std(r1, c1, r2, c2, val);
    }

    vector<int> row_sum(n, 0), col_sum(m, 0);
    {
        int cur = 0;
        for (int i = 0; i < n; ++i) {
            cur += rowDiff[i];
            row_sum[i] = cur;
        }
    }
    {
        int cur = 0;
        for (int j = 0; j < m; ++j) {
            cur += colDiff[j];
            col_sum[j] = cur;
        }
    }

    vector<int> row_dots(n, 0), col_dots(m, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.') {
                row_dots[i]++;
                col_dots[j]++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i > 0)
                diff[i][j] += diff[i - 1][j];
            if (j > 0)
                diff[i][j] += diff[i][j - 1];
            if (i > 0 && j > 0)
                diff[i][j] -= diff[i - 1][j - 1];
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int cand = row_sum[i] + col_sum[j] - diff[i][j] + row_dots[i] + col_dots[j] - (grid[i][j] == '.' ? 1 : 0);
            if (cand > ans)
                ans = cand;
        }
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
