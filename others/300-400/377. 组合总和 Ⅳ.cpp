#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

// 外层target求所有排列，顺序不同算不同的


class Solution {
public:
    int combinationSum4(vector<int> &nums, int target) {
        vector<unsigned int> dp(target + 1, 0);  // 使用unsigned int防止溢出
        dp[0] = 1;  // 初始化

        for (int i = 1; i <= target; i++) {
            for (int j : nums) {
                if (j <= i) {
                    dp[i] += dp[i - j];
                }
            }
        }
        return dp[target];
    }
};