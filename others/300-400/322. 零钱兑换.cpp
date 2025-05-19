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
#include <bitset>
#include <stack>

using namespace std;

class Solution {
public:
    int coinChange(vector<int> &coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, amount + 10000);
        dp[0] = 0;

        for (int i = 0; i < n; i++) {
            unsigned int coin = coins[i];
            for (unsigned int j = 0; j <= amount; j++) {
                if (j + coin <= amount) {
                    dp[j + coin] = min(dp[j + coin], dp[j] + 1);
                }
            }
        }

        return dp[amount] != amount + 10000 ? dp[amount] : -1;
    }
};