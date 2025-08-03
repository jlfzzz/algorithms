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

// 1 n^3, 2 n^2

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dp(n, vector<int>(n));
        dp[0] = grid[0];

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int mn = 1314520;
                for (int k = 0; k < n; k++) {
                    if (j == k) continue;
                    mn = min(mn, dp[i - 1][k]);
                }

                dp[i][j] = grid[i][j] + mn;
            }
        }

        return *ranges::min_element(dp[n - 1]);
    }
};

class Solution {
public:
    int minFallingPathSum(vector<vector<int>> &grid) {
        int n = grid.size();
        int first_min_sum = 0;
        int second_min_sum = 0;
        int first_min_index = -1;

        for (int i = 0; i < n; i++) {
            int cur_first_min_sum = INT_MAX;
            int cur_second_min_sum = INT_MAX;
            int cur_first_min_index = -1;

            for (int j = 0; j < n; j++) {
                int cur_sum = (j != first_min_index ? first_min_sum : second_min_sum) + grid[i][j];
                if (cur_sum < cur_first_min_sum) {
                    cur_second_min_sum = cur_first_min_sum;
                    cur_first_min_sum = cur_sum;
                    cur_first_min_index = j;
                } else if (cur_sum < cur_second_min_sum) {
                    cur_second_min_sum = cur_sum;
                }
            }
            first_min_sum = cur_first_min_sum;
            second_min_sum = cur_second_min_sum;
            first_min_index = cur_first_min_index;
        }
        return first_min_sum;
    }
};
