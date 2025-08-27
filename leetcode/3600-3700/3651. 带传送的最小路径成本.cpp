#include <bits/stdc++.h>

#include <ranges>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
#define i128 __int128_t
#define ull unsigned long long
constexpr long long inf = 0x3f3f3f3f / 2;


class Solution {
public:
    int minCost(vector<vector<int>> &grid, int k) {
        map<int, vector<pii>> mp;
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                mp[grid[i][j]].emplace_back(i + 1, j + 1);
            }
        }

        vector dis(m + 1, vector(n + 1, vector<int>(k + 1, inf)));
        for (int i = 0; i <= k; i++) {
            dis[0][1][i] = 0;
            dis[1][1][i] = 0;
        }

        for (int round = 0; round <= k; round++) {
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    int cost = grid[i - 1][j - 1];
                    int t = min(dis[i - 1][j][round], dis[i][j - 1][round]) + cost;
                    if (t < dis[i][j][round]) {
                        dis[i][j][round] = t;
                    }
                }
            }

            if (round + 1 <= k) {
                int mn = inf;
                for (auto &it: ranges::reverse_view(mp)) {
                    auto &v = it.second;
                    for (auto [x, y]: v) {
                        int cost = dis[x][y][round];
                        mn = min(mn, cost);
                    }
                    for (auto [x, y]: v) {
                        dis[x][y][round + 1] = min(dis[x][y][round], mn);
                    }
                }
            }
        }

        return dis[m][n][k];
    }
};
