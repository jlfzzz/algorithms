#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
constexpr int NEG = -1000000000;


class Solution {
public:
    int maxProfit(int n, vector<int> &present, vector<int> &future, vector<vector<int>> &hierarchy, int budget) {
        vector<vector<int>> g(n + 1, vector<int>());
        for (auto &v: hierarchy) {
            int a = v[0], b = v[1];
            g[a].push_back(b);
        }

        // 0 当前不选
        vector<vector<int>> dp0(n + 1, vector<int>(budget + 1, NEG));
        vector<vector<int>> dp1(n + 1, vector<int>(budget + 1, NEG));

        auto dfs = [&](this auto &&dfs, int u) -> void {
            for (int i = 0; i <= budget; i++)
                dp0[u][i] = dp1[u][i] = NEG;

            // 先合并子树收益 subF[j][0]/subF[j][1]
            vector<int> sub0(budget + 1, 0), sub1(budget + 1, 0);
            for (int v: g[u]) {
                dfs(v);
                vector<int> nsub0 = sub0, nsub1 = sub1;
                for (int j = budget; j >= 0; j--) {
                    for (int jy = 0; jy <= j; jy++) {
                        if (dp0[v][jy] != NEG)
                            nsub0[j] = max(nsub0[j], sub0[j - jy] + dp0[v][jy]);
                        if (dp1[v][jy] != NEG)
                            nsub1[j] = max(nsub1[j], sub1[j - jy] + dp1[v][jy]);
                    }
                }
                sub0.swap(nsub0);
                sub1.swap(nsub1);
            }

            // 再根据是否可以半价计算当前节点 u 的 f[j][k]
            int c0 = present[u - 1];
            int c1 = present[u - 1] / 2;
            int g0 = future[u - 1] - c0;
            int g1 = future[u - 1] - c1;
            for (int j = 0; j <= budget; j++) {
                dp0[u][j] = sub0[j];
                dp1[u][j] = sub0[j];
                if (j >= c0 && sub1[j - c0] != NEG)
                    dp0[u][j] = max(dp0[u][j], sub1[j - c0] + g0);
                if (j >= c1 && sub1[j - c1] != NEG)
                    dp1[u][j] = max(dp1[u][j], sub1[j - c1] + g1);
            }
        };

        dfs(1);
        return dp0[1][budget];
    }
};
