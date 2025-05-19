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

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 5000000));


        dp[0][1] = 0;
        dp[1][0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1];
            }
        }

        return dp[n][m];
    }
};

class Solution {
public:
    int minPathSum(vector<vector<int>> &grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));

        auto dfs = [&](this auto &&dfs, int row, int col) -> int {
            if (dp[row][col] != -1) return dp[row][col];

            int up = 100000;
            int left = 100000;
            if (col - 1 >= 0) left = dfs(row, col - 1);
            if (row - 1 >= 0) up = dfs(row - 1, col);

            if (up == 100000 && left == 100000) {
                dp[row][col] = grid[row][col];
            } else {
                dp[row][col] = min(left, up) + grid[row][col];
            }

            return dp[row][col];
            };

        return dfs(m - 1, n - 1);
    }
};