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
    int maxMoves(vector<vector<int>> &grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<bool>> dp(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++) {
            dp[i][0] = true;
        }

        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[j][i]) {
                    ans = max(ans, i);

                    if (i == m - 1) continue;
                    int currVal = grid[j][i];

                    if (j - 1 >= 0 && grid[j - 1][i + 1] > currVal) dp[j - 1][i + 1] = true;
                    if (grid[j][i + 1] > currVal) dp[j][i + 1] = true;
                    if (j + 1 < n && grid[j + 1][i + 1] > currVal) dp[j + 1][i + 1] = true;
                }
            }
        }

        return ans;
    }
};