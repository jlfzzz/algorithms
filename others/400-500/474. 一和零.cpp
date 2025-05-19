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
    int findMaxForm(vector<string> &strs, int m, int ones_limit) {
        int n = strs.size();

        // 预处理：计算每个字符串的 0 和 1 的数量
        // 使用 vector<pair<int, int>> 是可以的，但也可以直接在主循环中计算
        // 这里保留预处理部分，但可以省略 nums 这个中间变量
        vector<pair<int, int>> nums(n);
        for (int i = 0; i < n; ++i) {
            int zeros = 0;
            int ones = 0;
            for (char c : strs[i]) {
                if (c == '1') {
                    ones++;
                } else {
                    zeros++;
                }
            }
            nums[i] = { zeros, ones };
        }

        // 初始化 DP 数组
        // dp[j][k] 表示使用最多 j 个 '0' 和最多 k 个 '1' 时，能构成的最大子集的大小
        // 大小需要是 (m + 1) x (ones_limit + 1)
        vector<vector<int>> dp(m + 1, vector<int>(ones_limit + 1, 0));

        // 遍历每个字符串（物品）
        for (int i = 0; i < n; i++) {
            int curr_zeros = nums[i].first;
            int curr_ones = nums[i].second;

            // 遍历背包容量（0 的数量） - 必须从大到小
            for (int j = m; j >= curr_zeros; j--) {
                // 遍历背包容量（1 的数量） - 必须从大到小
                for (int k = ones_limit; k >= curr_ones; k--) {
                    // 状态转移方程：
                    // 不选第 i 个字符串：dp[j][k] 保持不变
                    // 选第 i 个字符串：dp[j - curr_zeros][k - curr_ones] + 1
                    // 取两者最大值
                    dp[j][k] = max(dp[j][k], dp[j - curr_zeros][k - curr_ones] + 1);
                }
            }
        }

        // 最终答案是使用不超过 m 个 '0' 和 ones_limit 个 '1' 所能达到的最大子集大小
        return dp[m][ones_limit];
    }
};