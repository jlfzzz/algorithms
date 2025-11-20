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

int H, W;
vector<int> grid;
int dp[8][1 << 7];
bool vis[8][1 << 7];

int dfs(int i, int mask1) {
    if (i == H)
        return 0;
    if (vis[i][mask1])
        return dp[i][mask1];
    vis[i][mask1] = true;

    int res = 1e9;
    for (int mask2 = 0; mask2 < (1 << W); mask2++) {
        if ((mask2 & grid[i]) != mask2)
            continue;
        bool ok = true;
        for (int j = 0; j + 1 < W; j++) {
            if ((mask1 >> j & 3) == 3 && (mask2 >> j & 3) == 3) {
                ok = false;
                break;
            }
        }
        if (!ok)
            continue;
        int cost = __builtin_popcount(grid[i]) - __builtin_popcount(mask2);
        res = min(res, cost + dfs(i + 1, mask2));
    }

    return dp[i][mask1] = res;
}

void solve() {
    cin >> H >> W;
    grid.assign(H, 0);
    for (int i = 0; i < H; i++) {
        string s;
        cin >> s;
        int m = 0;
        for (int j = 0; j < W; j++) {
            if (s[j] == '#') 
                m |= (1 << j);
        }
        grid[i] = m;
    }

    memset(vis, 0, sizeof(vis));
    cout << dfs(0, 0) << "\n";
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
