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
    int maxProductPath(vector<vector<int>> &grid) {
        int n = grid.size();
        if (n == 0) return -1; // Handle empty grid case
        int m = grid[0].size();
        if (m == 0) return -1; // Handle empty row case

        long long mod = 1e9 + 7;

        // dp[i][j].first = max product to reach (i, j)
        // dp[i][j].second = min product to reach (i, j)
        // Using 0-based indexing consistent with grid
        vector<vector<pair<long long, long long>>> dp(n, vector<pair<long long, long long>>(m));

        // Initialize the starting cell
        dp[0][0].first = grid[0][0];
        dp[0][0].second = grid[0][0];

        // Initialize the first row (can only come from the left)
        for (int j = 1; j < m; ++j) {
            long long curr = grid[0][j];
            long long prev_max = dp[0][j - 1].first;
            long long prev_min = dp[0][j - 1].second;
            // Max and min are determined by multiplying the current value with the previous max and min
            dp[0][j].first = max(prev_max * curr, prev_min * curr);
            dp[0][j].second = min(prev_max * curr, prev_min * curr);
        }

        // Initialize the first column (can only come from the top)
        for (int i = 1; i < n; ++i) {
            long long curr = grid[i][0];
            long long prev_max = dp[i - 1][0].first;
            long long prev_min = dp[i - 1][0].second;
            dp[i][0].first = max(prev_max * curr, prev_min * curr);
            dp[i][0].second = min(prev_max * curr, prev_min * curr);
        }

        // Fill the rest of the dp table
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < m; ++j) {
                long long curr = grid[i][j];

                // Get max and min products from the cell above
                long long up_max = dp[i - 1][j].first;
                long long up_min = dp[i - 1][j].second;

                // Get max and min products from the cell to the left
                long long left_max = dp[i][j - 1].first;
                long long left_min = dp[i][j - 1].second;

                // Calculate the four possible product candidates
                long long prod1 = up_max * curr;
                long long prod2 = up_min * curr;
                long long prod3 = left_max * curr;
                long long prod4 = left_min * curr;

                // The new max is the maximum of all candidates
                dp[i][j].first = max({ prod1, prod2, prod3, prod4 });
                // The new min is the minimum of all candidates
                dp[i][j].second = min({ prod1, prod2, prod3, prod4 });
            }
        }

        // Get the maximum product at the bottom-right cell
        long long final_max_prod = dp[n - 1][m - 1].first;

        // If the maximum product is negative, return -1
        if (final_max_prod < 0) {
            return -1;
        } else {
            // Otherwise, return the result modulo 10^9 + 7
            // Ensure the result of modulo is non-negative if needed, though final_max_prod is guaranteed non-negative here.
            return (int)(final_max_prod % mod);
        }
    }
};