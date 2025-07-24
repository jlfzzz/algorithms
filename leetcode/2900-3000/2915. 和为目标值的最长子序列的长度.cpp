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

using namespace std;

class Solution {
public:
    int lengthOfLongestSubsequence(vector<int> &nums, int target) {
        vector<int> dp(target + 1, -1);
        dp[0] = 0;

        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            for (int j = target; j >= x; j--) {
                if (dp[j - x] != -1) {
                    dp[j] = max(dp[j - x] + 1, dp[j]);
                }

            }
        }

        return dp[target];
    }
};