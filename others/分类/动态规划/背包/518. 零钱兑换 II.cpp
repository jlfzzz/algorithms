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
    int change(int amount, vector<int> &coins) {
        int n = coins.size();
        vector<vector<unsigned int>> dp(n + 1, vector<unsigned int>(amount + 1, 0));

        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            dp[i][0] = 1;
            for (int j = 0; j <= amount; j++) {
                dp[i][j] = dp[i - 1][j];

                if (coins[i - 1] <= j) {
                    dp[i][j] += dp[i][j - coins[i - 1]];
                }
            }
        }
        return dp[n][amount];
    }
};