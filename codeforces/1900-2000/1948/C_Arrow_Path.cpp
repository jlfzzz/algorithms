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

void solve() {
    int n;
    cin >> n;
    vector<vector<char>> grid(2, vector<char>(n));
    For(i, n) cin >> grid[0][i];
    For(i, n) cin >> grid[1][i];

    vector<vector<vector<int>>> memo(2, vector<vector<int>>(n, vector<int>(2, 0)));

    auto dfs = [&](this auto &&dfs, int i, int j, int f) -> bool {
        if (i < 0 || i >= 2 || j < 0 || j >= n)
            return false;

        if (memo[i][j][f] == 1)
            return false;
        if (memo[i][j][f] == 2)
            return true;
        if (memo[i][j][f] == 3)
            return false;

        if (i == 1 && j == n - 1)
            return true;

        memo[i][j][f] = 1;
        bool res = false;

        if (f) {
            if (grid[i][j] == '<' && j - 1 >= 0) {
                res |= dfs(i, j - 1, !f);
            } else if (grid[i][j] == '>' && j + 1 < n) {
                res |= dfs(i, j + 1, !f);
            }
        } else {
            if (i == 0)
                res |= dfs(i + 1, j, 1);
            if (j + 1 < n)
                res |= dfs(i, j + 1, 1);
            if (i - 1 >= 0)
                res |= dfs(i - 1, j, 1);
            if (j - 1 >= 0)
                res |= dfs(i, j - 1, 1);
        }

        memo[i][j][f] = res ? 2 : 3;
        return res;
    };

    bool f = dfs(0, 0, 0);
    cout << (f ? "YES\n" : "NO\n");
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
