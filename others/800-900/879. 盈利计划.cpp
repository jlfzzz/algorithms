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

// 记忆化 and 背包

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        int size = profit.size();
        int MOD = 1e9 + 7;

        // 修改 memo 为三维: [index][people][capped_profit]
        // 大小: [项目数][人数上限+1][最低利润+1]
        vector<vector<vector<int>>> memo(size + 1, vector<vector<int>>(n + 1, vector<int>(minProfit + 1, -1)));

        // auto dfs = [&](auto& dfs, int index, int people, int curr_profit) -> int { // C++14/17 风格
        auto dfs = [&](this auto&& dfs, int index, int people, int curr_profit) -> int { // C++23 风格
            // 基本情况 1: 人数超限 (或者也可以在调用前检查)
            if (people > n) {
                return 0;
            }

            // 基本情况 2: 所有项目都已考虑
            if (index == size) {
                // 满足最低利润要求则为 1 种方案，否则为 0
                return curr_profit >= minProfit ? 1 : 0;
            }

            // 使用“封顶”利润进行记忆化查找
            // 任何 >= minProfit 的利润，在状态中都视为 minProfit
            int capped_profit = min(curr_profit, minProfit);
            if (memo[index][people][capped_profit] != -1) {
                return memo[index][people][capped_profit];
            }

            // 递归计算
            // 方案 1: 不选当前项目 (index)
            long long ways = dfs(index + 1, people, curr_profit); // 使用 long long 避免中间结果溢出

            // 方案 2: 选择当前项目 (index), 如果人数允许
            int next_people = people + group[index];
            if (next_people <= n) {
                // 注意：传递给下一层的 profit 是 *实际* 增加后的 profit
                // 但存入 memo 时是用 capped_profit
                int next_profit = curr_profit + profit[index];
                ways = (ways + dfs(index + 1, next_people, next_profit)) % MOD;
            }

            // 将结果存入记忆化表 (使用 index, people, capped_profit 作为索引)
            memo[index][people][capped_profit] = (int)ways;
            return (int)ways;
        };

        // 从第 0 个项目开始，当前 0 人，0 利润
        return dfs(0, 0, 0);
    }
};

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int> &group, vector<int> &profit) {
        int size = group.size();
        int MOD = 1e9 + 7;
        // dp[j][k] := 使用恰好 j 个人，产生至少 k 利润的方案数
        // k 的范围是 [0, minProfit]
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));

        // 基础状态：0 个人，利润 >= 0 的方案有 1 种（什么都不做）
        dp[0][0] = 1;

        for (int i = 0; i < size; ++i) { // 遍历每个罪行
            int g = group[i];
            int p = profit[i];

            // 从后往前遍历人数 j，确保每个罪行只用一次
            for (int j = n; j >= g; --j) {
                // 从后往前遍历利润 k
                for (int k = minProfit; k >= 0; --k) {
                    // 计算如果选择当前罪行，之前的状态需要满足的最低利润
                    // 如果 k - p < 0，意味着加上 p 后利润肯定超过 k，只需要之前利润 >= 0 即可
                    // 所以之前的利润需求是 max(0, k - p)
                    int prev_k_needed = max(0, k - p);

                    // 状态转移：
                    // dp[j][k] 的新值 = 不选罪行 i 的方案数 (dp[j][k] 旧值)
                    //                 + 选择罪行 i 的方案数 (来自 dp[j - g][prev_k_needed])
                    dp[j][k] = (dp[j][k] + dp[j - g][prev_k_needed]) % MOD;
                }
            }
        }

        // 最终结果是所有人数 j (0 <= j <= n) 情况下，利润至少为 minProfit 的方案总数
        long long total_schemes = 0;
        for (int j = 0; j <= n; ++j) {
            total_schemes = (total_schemes + dp[j][minProfit]) % MOD;
        }

        return (int)total_schemes;
    }
};