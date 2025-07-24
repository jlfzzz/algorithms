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

using namespace std;

class Solution {
public:
    int tallestBillboard(vector<int> &rods) {
        int n = rods.size();
        vector<int> dp = { 0 };
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += rods[i];
            vector<int> new_dp(sum + 1, INT_MIN);
            for (int diff = 0; diff <= sum - rods[i]; ++diff) {
                if (dp[diff] != INT_MIN) {
                    // 不选当前rod，保留原状态
                    new_dp[diff] = max(new_dp[diff], dp[diff]);
                    // 选当前rod，加到较高的支架
                    new_dp[diff + rods[i]] = max(new_dp[diff + rods[i]], dp[diff] + rods[i]);
                    // 选当前rod，加到较低的支架
                    int new_diff = abs(diff - rods[i]);
                    int new_height = dp[diff] + max(rods[i] - diff, 0);
                    new_dp[new_diff] = max(new_dp[new_diff], new_height);
                }
            }
            dp = new_dp;
        }
        return dp[0] == INT_MIN ? 0 : dp[0];
    }
};