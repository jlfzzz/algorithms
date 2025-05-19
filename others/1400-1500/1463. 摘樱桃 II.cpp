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
#include <array> 

using namespace std;

class Solution {
public:
    int cherryPickup(vector<vector<int>> &grid) {
        int row = grid.size();
        int col = grid[0].size();
        vector<vector<vector<int>>> dp(row, vector<vector<int>>(col + 2, vector<int>(col + 2)));
        dp[0][1][col] = grid[0][0] + grid[0][col - 1];

        for (int i = 1; i < row; i++) {
            for (int j = 1; j <= min(col, i + 1); j++) {
                for (int k = col; k >= max(j + 1, col - i); k--) {
                    dp[i][j][k] = max({ dp[i - 1][j - 1][k - 1], dp[i - 1][j - 1][k], dp[i - 1][j - 1][k + 1],
                                        dp[i - 1][j][k - 1], dp[i - 1][j][k], dp[i - 1][j][k + 1],
                                        dp[i - 1][j + 1][k - 1], dp[i - 1][j + 1][k], dp[i - 1][j + 1][k + 1] })
                        + grid[i][j - 1] + grid[i][k - 1];
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= col; i++) {
            for (int j = 1; j <= col; j++) {
                ans = max(ans, dp[row - 1][i][j]);
            }
        }
        return ans;
    }
};

class Solution {
public:
    int cherryPickup(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<vector<int>>> f(m + 1, vector<vector<int>>(n + 2, vector<int>(n + 2)));
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < min(n, i + 1); j++) {
                for (int k = max(j + 1, n - 1 - i); k < n; k++) {
                    f[i][j + 1][k + 1] = max({
                        f[i + 1][j][k], f[i + 1][j][k + 1], f[i + 1][j][k + 2],
                        f[i + 1][j + 1][k], f[i + 1][j + 1][k + 1], f[i + 1][j + 1][k + 2],
                        f[i + 1][j + 2][k], f[i + 1][j + 2][k + 1], f[i + 1][j + 2][k + 2],
                        }) + grid[i][j] + grid[i][k];
                }
            }
        }
        return f[0][1][n];
    }
};

class Solution {
public:
    int cherryPickup(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> pre(n + 2, vector<int>(n + 2));
        vector<vector<int>> cur(n + 2, vector<int>(n + 2));
        for (int i = m - 1; i >= 0; i--) {
            for (int j = 0; j < min(n, i + 1); j++) {
                for (int k = max(j + 1, n - 1 - i); k < n; k++) {
                    cur[j + 1][k + 1] = max({
                        pre[j][k], pre[j][k + 1], pre[j][k + 2],
                        pre[j + 1][k], pre[j + 1][k + 1], pre[j + 1][k + 2],
                        pre[j + 2][k], pre[j + 2][k + 1], pre[j + 2][k + 2],
                        }) + grid[i][j] + grid[i][k];
                }
            }
            swap(pre, cur); // 下一个 i 的 pre 是 cur
        }
        return pre[1][n];
    }
};