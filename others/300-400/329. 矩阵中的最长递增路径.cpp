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

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>> &matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        int ans = 1;

        int directions[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

        auto dfs = [&](this auto &&dfs, int i, int j) -> int {
            if (dp[i][j] != 0)
                return dp[i][j];

            dp[i][j]++;

            for (auto &v : directions) {
                int dx = v[0];
                int dy = v[1];

                if (i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m && matrix[i + dx][j + dy] > matrix[i][j]) {
                    dp[i][j] = max(dp[i][j], dfs(i + dx, j + dy) + 1);
                }
            }
            return dp[i][j];
            };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans = max(ans, dfs(i, j));
            }
        }

        return ans;
    }
};