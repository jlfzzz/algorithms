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
    // Assuming the function name implies target XOR value is k
    int countPathsWithXorValue(vector<vector<int>> &grid, int k) {
        int n = grid.size();
        if (n == 0) return 0;
        int m = grid[0].size();
        if (m == 0) return 0;

        int maxXor = 16;
        int mod = 1000000007; // Standard modulo for path counting problems

        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(maxXor, 0)));

        // Base case: Starting cell (0, 0) -> dp[1][1]
        int start_val = grid[0][0];
        dp[1][1][start_val] = 1;

        if (k < 0 || k >= maxXor) {
            return 0; // Target k is outside the range [0, maxXor-1] we tracked.
        }

        // Fill the DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // Skip base case as it's already initialized outside the loop
                if (i == 1 && j == 1) continue;

                int curr_val = grid[i - 1][j - 1];

                // Iterate through all possible XOR sums 'x' we might achieve at cell (i, j)
                for (int x = 0; x < maxXor; ++x) {
                    // Calculate the required XOR sum from the previous step
                    int prev_xor = x ^ curr_val;

                    // If prev_xor is outside the tracked range, paths leading to it
                    // are effectively 0 in our DP table.

                    // Get paths from above (dp[i-1][j]), checking boundary i > 1
                    // int paths_from_up = (i > 1) ? dp[i - 1][j][prev_xor] : 0;
                    int paths_from_up = dp[i - 1][j][prev_xor];

                    // Get paths from left (dp[i][j-1]), checking boundary j > 1
                    //int paths_from_left = (j > 1) ? dp[i][j - 1][prev_xor] : 0;
                    int paths_from_left = dp[i][j - 1][prev_xor];

                    // Update the count for achieving XOR sum 'x' at cell (i, j)
                    // Use long long for intermediate sum to prevent overflow before modulo
                    dp[i][j][x] = (int)(((long long)paths_from_up + paths_from_left) % mod);
                }
            }
        }

        // The result is the number of paths to the bottom-right cell (n-1, m-1) -> dp[n][m]
        // with the target XOR sum k.
        // Check if k is within the tracked range.

        return dp[n][m][k];
    }
};