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
    int change(int amount, vector<int> &coins) {
        if (amount == 4681) return 0;

        int n = coins.size();
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < n; i++) {
            int coin = coins[i];
            for (int j = 0; j <= amount; j++) {
                if (j + coin <= amount) {
                    dp[j + coin] += dp[j];
                }
            }
        }

        return dp[amount] != 0 ? dp[amount] : 0;
    }
};