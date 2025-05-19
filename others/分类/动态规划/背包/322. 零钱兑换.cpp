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
    int coinChange(vector<int> &coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, amount + 1));

        dp[0][0] = 0;
        for (int i = 1; i <= n;i++) {
            dp[i][0] = 0;
            for (int j = 0; j <= amount; j++) {
                //转移
                dp[i][j] = dp[i - 1][j];

                if (coins[i - 1] <= j) {
                    dp[i][j] = min(dp[i][j], dp[i][j - coins[i - 1]] + 1);
                }
            }
        }
        return dp[n][amount] != amount + 1 ? dp[n][amount] : -1;

    }
};

class Solution {
public:
    int coinChange(vector<int> &coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;

        for (int i = 1; i <= amount; i++) {
            for (int x : coins) {
                if (x <= i) {
                    dp[i] = min(dp[i], dp[i - x] + 1);
                }
            }
        }
        return dp[amount] != amount + 1 ? dp[amount] : -1;
    }
};