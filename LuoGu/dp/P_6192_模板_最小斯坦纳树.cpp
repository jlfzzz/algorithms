#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>


using namespace std;

const int MAXN = 105;
const int INF = 0x3f3f3f3f;

// dp[i][s]: 以 i 为根，包含了状态 s 的最小权值和
int dp[MAXN][1 << 10];
// dist[i][j]: 预处理的两点间最短距离
int dist[MAXN][MAXN];

int n, m, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> k;

    // 1. 初始化 dist 数组
    // 注意：如果有重边，读入时要取 min，这里先初始化为 INF
    memset(dist, 0x3f, sizeof(dist));
    for (int i = 1; i <= n; ++i)
        dist[i][i] = 0;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }

    // 2. 预处理 Floyd (O(n^3))
    // 这一步在 DP 之前做，不用重复计算
    for (int p = 1; p <= n; ++p) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][p] != INF && dist[p][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][p] + dist[p][j]);
                }
            }
        }
    }

    // 3. 初始化 DP
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < k; ++i) {
        int p;
        cin >> p;
        dp[p][1 << i] = 0;
    }

    // 4. 状压 DP
    int max_mask = (1 << k);
    for (int mask = 1; mask < max_mask; ++mask) {

        // 第一步：同根合并 (O(n * 3^k))
        for (int i = 1; i <= n; ++i) {
            for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
                dp[i][mask] = min(dp[i][mask], dp[i][sub] + dp[i][mask ^ sub]);
            }
        }

        // 第二步：换根转移 (利用预处理的 dist) (O(n^2 * 2^k))
        // 尝试用 j 作为根，通过 j -> i 的最短路来更新 i 作为根的代价
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[j][i] != INF) { // 如果 j 能到达 i
                    dp[i][mask] = min(dp[i][mask], dp[j][mask] + dist[j][i]);
                }
            }
        }
    }

    // 5. 统计答案
    int ans = INF;
    int full_mask = (1 << k) - 1;
    for (int i = 1; i <= n; ++i) {
        ans = min(ans, dp[i][full_mask]);
    }

    cout << ans << endl;

    return 0;
}
