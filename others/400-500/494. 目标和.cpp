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

// 0 1 背包每次所用的状态都得是上次， 避免重复使用。 所以用一个额外数组保存

#include <vector>
#include <numeric> // 包含 numeric 头文件以防需要计算总和等操作

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int> &nums, int target) {
        // dp[j] 表示和为 j - 1000 的表达式数目
        // 数组大小 2001 覆盖了从 -1000 到 1000 的和范围
        vector<int> dp(2001, 0);
        // 初始状态：和为 0 (索引 1000) 的方法数为 1
        dp[1000] = 1;

        int n = nums.size();
        for (int i = 0; i < n; i++) {
            // 使用临时数组存储当前轮次的计算结果
            vector<int> temp(2001, 0);
            int num = nums[i];
            // 遍历上一轮所有可能的和 j
            for (int j = 0; j < 2001; j++) {
                // 如果 dp[j] > 0，说明和 j - 1000 是可达的
                if (dp[j] > 0) {

                    // 应该是 j - 1000 +- num + 1000, 1000 抵消了

                    // 考虑添加 num 的情况
                    int next_add_idx = j + num;
                    if (next_add_idx < 2001) { // 检查索引是否越界
                        temp[next_add_idx] += dp[j];
                    }
                    // 考虑减去 num 的情况
                    int next_sub_idx = j - num;
                    if (next_sub_idx >= 0) { // 检查索引是否越界
                        temp[next_sub_idx] += dp[j];
                    }
                }
            }
            // 更新 dp 数组为当前轮次的结果
            dp = temp;
        }

        // 目标和 target 对应的索引是 target + 1000
        // 检查 target + 1000 是否在有效范围内 (虽然根据题目约束通常是有效的)
        if (target + 1000 < 0 || target + 1000 >= 2001) {
            return 0;
        }
        return dp[target + 1000];
    }
};


class Solution {
public:
    int findTargetSumWays(std::vector<int> &nums, int target) {
        // 计算数组元素的总和
        // 使用 long long 防止潜在的整数溢出，尽管对于典型约束 int 可能足够
        long long total_sum = 0;
        for (int num  : nums) {
            total_sum += num;
        }
        // 或者使用 std::accumulate:
        // long long total_sum = std::accumulate(nums.begin(), nums.end(), 0LL); // 0LL 表示初始值为 long long 类型

        // 问题转化为找到一个子集 P，使得 sum(P) = (target + total_sum) / 2
        // 设 new_target = sum(P)

        // 检查边界条件：
        // 1. sum(P) 必须是非负数，所以 target + total_sum >= 0
        // 2. sum(P) 必须是整数，所以 target + total_sum 必须是偶数
        //    注意： C++ 中负数的模运算结果可能依赖于实现或为负，
        //    但 (target + total_sum) < 0 这个条件已经处理了 sum(P) < 0 的情况。
        //    如果 target + total_sum >= 0，则 (target + total_sum) % 2 != 0 可靠地检查奇偶性。
        if (total_sum + target < 0 || (total_sum + target) % 2 != 0) {
            return 0;
        }

        // 计算目标子集和
        int new_target = (total_sum + target) / 2;

        // 初始化 dp 数组
        // dp[j] 表示和为 j 的子集个数
        // 大小为 new_target + 1，所有元素初始化为 0
        std::vector<int> dp(new_target + 1, 0);

        // 和为 0 的方案只有一种（不选任何元素）
        dp[0] = 1;

        // 动态规划计算（0/1 背包问题）
        for (int num : nums) {
            // 从后往前遍历，以避免在当前迭代中重复使用同一个数字 num
            for (int j = new_target; j >= num; --j) {
                // 如果当前的和 j 大于等于 num，
                // 那么凑成和 j 的方案数可以增加凑成和 j - num 的方案数
                dp[j] += dp[j - num];
            }
        }

        // dp[new_target] 存储了和为 new_target 的子集个数
        return dp[new_target];
    }
};