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

// 如果 k 很大， m,n不是很大， 考虑 “折半 网格”

class Solution {
public:
    int numberOfPaths(vector<vector<int>> &grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(k)));

        for (int kIdx = 0; kIdx < k; kIdx++) {
            dp[1][1][grid[0][0] % k] = 1;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (i == 1 && j == 1) continue;

                auto &left = dp[i][j - 1];
                auto &up = dp[i - 1][j];
                int currVal = grid[i - 1][j - 1];

                for (int kIdx = 0; kIdx < k; kIdx++) {
                    dp[i][j][(kIdx + currVal) % k] = (left[kIdx] + up[kIdx]) % 1000000007;
                }
            }
        }

        return dp[n][m][0];
    }
};