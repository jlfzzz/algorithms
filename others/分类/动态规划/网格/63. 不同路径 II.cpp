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

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));

        if (obstacleGrid[0][0]) return 0;

        dp[1][1] = 1;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == 1 && j == 1) continue;

                if (obstacleGrid[i - 1][j - 1]) continue;

                int left = 0, up = 0;
                if (j - 2 >= 0) left = obstacleGrid[i - 1][j - 2] ? 0 : dp[i][j - 1];
                if (i - 2 >= 0) up = obstacleGrid[i - 2][j - 1] ? 0 : dp[i - 1][j];

                dp[i][j] = left + up;
            }
        }
        return dp[m][n];
    }
};