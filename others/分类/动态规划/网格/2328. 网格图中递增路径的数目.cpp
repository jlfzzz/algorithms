#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>

using namespace std;

#include <vector>

using namespace std;

class Solution {
    int n, m;
    long long mod = 1e9 + 7;
    vector<vector<long long>> dp;
    int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    long long dfs(int i, int j, const vector<vector<int>> &grid) {
        // 如果已经计算过，直接返回
        if (dp[i][j] != 0) {
            return dp[i][j];
        }

        // 初始化路径数为 1，代表 (i, j) 本身这条路径
        long long count = 1;

        // 遍历邻居
        for (auto &dir : directions) {
            int ni = i + dir[0];
            int nj = j + dir[1];

            // 检查边界和递增条件
            if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] > grid[i][j]) {
                // 累加从邻居出发的路径数，并取模
                count = (count + dfs(ni, nj, grid)) % mod;
            }
        }

        // 缓存结果并返回
        dp[i][j] = count;
        return dp[i][j];
    }

public:
    int countPaths(vector<vector<int>> &grid) {
        n = grid.size();
        m = grid[0].size();
        // 初始化 dp 数组，用 0 表示未计算
        dp.assign(n, vector<long long>(m, 0));

        long long total_paths = 0;

        // 遍历所有单元格作为起点
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // 累加从每个单元格出发的路径数，并取模
                total_paths = (total_paths + dfs(i, j, grid)) % mod;
            }
        }

        return (int)total_paths;
    }
};