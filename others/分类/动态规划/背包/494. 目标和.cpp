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

class Solution {
public:
    int findTargetSumWays(vector<int> &nums, int target) {
        const int OFFSET = 1000;
        const int MAXSUM = 2000;  // 下标 0…2000 对应的实际 sum 为 -1000…1000
        vector<int> dp(MAXSUM + 1, 0), next_dp(MAXSUM + 1, 0);
        dp[OFFSET] = 1;  // sum = 0 的方法数为 1

        for (int x : nums) {
            // 每轮都要重置 next_dp
            fill(next_dp.begin(), next_dp.end(), 0);
            for (int j = 0; j <= MAXSUM; j++) {
                if (dp[j] == 0) continue;
                int ways = dp[j];
                // 对应实际 sum = j - OFFSET

                // 加 +
                int pos = j + x;
                if (pos <= MAXSUM) {
                    next_dp[pos] += ways;
                }
                // 加 -
                int neg = j - x;
                if (neg >= 0) {
                    next_dp[neg] += ways;
                }
            }
            // 交换 dp 和 next_dp
            dp.swap(next_dp);
        }

        int idx = target + OFFSET;
        return (idx >= 0 && idx <= MAXSUM) ? dp[idx] : 0;
    }
};


class Solution {
public:
    int findTargetSumWays(std::vector<int> &nums, int target) {
        // 计算数组元素的总和
        // 使用 long long 防止潜在的整数溢出，尽管对于典型约束 int 可能足够
        long long total_sum = 0;
        for (int num : nums) {
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