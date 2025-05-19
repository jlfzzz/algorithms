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
    vector<int> pathsWithMaxScore(vector<string> &board) {
        int n = board.size();
        int mod = 1000000007;

        // dp[i][j] = {max_score, path_count} to reach cell (i-1, j-1)
        vector<vector<pair<int, int>>> dp(n + 1, vector<pair<int, int>>(n + 1, { -1, 0 }));

        // Base case: Starting point (0, 0) which corresponds to dp[1][1]
        // Score starts at 0, one way to reach it (itself)
        dp[1][1] = { 0, 1 };

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                // Skip the starting cell as it's already initialized
                if (i == 1 && j == 1) continue;

                char current_char = board[i - 1][j - 1];
                // If the cell is blocked, skip it
                if (current_char == 'X') continue;

                // Get potential predecessors
                auto &left = dp[i][j - 1];
                auto &up = dp[i - 1][j];
                auto &leftUp = dp[i - 1][j - 1];

                // Find the maximum score among reachable predecessors
                int max_score = -1;
                if (left.first != -1) max_score = max(max_score, left.first);
                if (up.first != -1) max_score = max(max_score, up.first);
                if (leftUp.first != -1) max_score = max(max_score, leftUp.first);


                // If no predecessors are reachable, this cell is also unreachable
                if (max_score == -1) continue;

                // Calculate the number of paths leading to this max_score
                long long path_count = 0; // Use long long to prevent overflow before modulo
                if (left.first == max_score) {
                    path_count = (path_count + left.second) % mod;
                }
                if (up.first == max_score) {
                    path_count = (path_count + up.second) % mod;
                }
                if (leftUp.first == max_score) {
                    path_count = (path_count + leftUp.second) % mod;
                }

                // Calculate the score for the current cell
                // Treat 'E' and 'S' as 0 score, otherwise use the digit's value
                // Corrected indexing: board[i-1][j-1]
                // Score calculation does NOT use modulo
                int current_score = (current_char == 'E' || current_char == 'S') ? 0 : current_char - '0';


                dp[i][j].first = max_score + current_score;
                dp[i][j].second = (int)path_count; // Cast back to int after modulo
            }
        } // End of inner loop
          // End of outer loop - Return statement should be AFTER the loops

        // Get the result from the bottom-right cell dp[n][n]
        auto &result = dp[n][n];
        return result.first == -1 ? vector<int>{0, 0} : vector<int>{ result.first, result.second };
    }
};