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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    For(i, n) {
        string s;
        cin >> s;
        For(j, m) { grid[i][j] = s[j]; }
    }

    vector<vector<int>> vis(n, vector<int>(m, -1));

    auto dfs = [&](this auto &&dfs, int i, int j) -> int {
        if (i < 0 or i == n or j < 0 or j == m) {
            return 1;
        }

        int &x = vis[i][j];
        if (x != -1) {
            return x;
        }

        x = 0;
        if (grid[i][j] == 'U') {
            x = dfs(i - 1, j);
        } else if (grid[i][j] == 'L') {
            x = dfs(i, j - 1);
        } else if (grid[i][j] == 'R') {
            x = dfs(i, j + 1);
        } else if (grid[i][j] == 'D') {
            x = dfs(i + 1, j);
        } else {
            x = dfs(i + 1, j) and dfs(i - 1, j) and dfs(i, j - 1) and dfs(i, j + 1);
        }
        return x;
    };

    int ans = 0;
    For(i, n) {
        For(j, m) { ans += !dfs(i, j); }
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
