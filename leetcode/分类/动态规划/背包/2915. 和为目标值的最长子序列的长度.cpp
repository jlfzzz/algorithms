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
    int lengthOfLongestSubsequence(vector<int> &nums, int target) {
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, -1));

        for (int i = 0; i <= n; i++) {
            dp[i][0] = 0;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= target; j++) {
                dp[i][j] = dp[i - 1][j]; // 不选

                int curr = nums[i - 1]; // 修正索引
                if (curr <= j && dp[i - 1][j - curr] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - curr] + 1);
                }
            }
        }

        return dp[n][target] != -1 ? dp[n][target] : -1; // 如果不存在则返回-1
    }
};


class Solution {
public:
    int lengthOfLongestSubsequence(std::vector<int> &nums, int target) {
        // dp[k] 表示和为 k 的最长子序列的长度。
        // 初始化为 -1 表示无法达到该和。
        std::vector<int> dp(target + 1, -1);

        // 和为 0 的子序列是空子序列，长度为 0。
        dp[0] = 0;

        // 遍历 nums 中的每个数字 (物品)
        for (int num : nums) {
            // 遍历可能的和 (背包容量)，从 target 向下到 num
            // 倒序遍历确保每个 num 在构成子序列和时只被考虑一次 (0/1 背包)
            for (int k = target; k >= num; --k) {
                // 如果 dp[k - num] 不是 -1，意味着可以构成和为 k - num 的子序列
                if (dp[k - num] != -1) {
                    // 我们可以尝试通过添加 num 来构成和为 k 的子序列
                    // 新的长度是 dp[k - num] + 1
                    // 更新 dp[k] 为当前找到的构成和 k 的最大长度
                    dp[k] = std::max(dp[k], dp[k - num] + 1);
                }
            }
        }

        // 返回和为 target 的最长子序列长度
        // 如果 dp[target] 仍为 -1，则表示没有子序列的和等于 target
        return dp[target];
    }
};