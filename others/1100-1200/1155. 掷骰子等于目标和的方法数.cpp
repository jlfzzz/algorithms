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
#include <set>
#include <random>

using namespace std;

class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        if (target < n || target > n * k) {
            return 0; // 无法组成 target
        }
        const int MOD = 1'000'000'007;
        vector<long long> f(target - n + 1);
        f[0] = 1;
        for (int i = 1; i <= n; i++) {
            int max_j = min(i * (k - 1), target - n); // i 个骰子至多掷出 i*(k-1)
            for (int j = 1; j <= max_j; j++) {
                f[j] += f[j - 1]; // 原地计算 f 的前缀和
            }
            for (int j = max_j; j >= k; j--) {
                f[j] = (f[j] - f[j - k]) % MOD; // f[j] 是两个前缀和的差
            }
        }
        return f.back();
    }
};

class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        std::vector<int> dp(target + 1, 0); // dp[j] 表示用当前考虑到的骰子数量，掷出和为 j 的方法数
        dp[0] = 1; // 初始状态：用0个骰子，掷出和为0的方法有1种。
        // 这作为后续计算的起点。对于有骰子的情况，dp[0]应为0。

        const int MOD = 1e9 + 7;

        for (int i = 1; i <= n; i++) { // 代表正在考虑第 i 个骰子
            std::vector<int> new_dp(target + 1, 0); // 存储用 i 个骰子得到各个和的方法数
            long long current_window_sum = 0;

            // max_sum_this_iteration 是用 i 个骰子能达到的最大和，但不超过 target
            int max_sum_this_iteration = std::min(i * k, target);
            // min_sum_this_iteration 是用 i 个骰子能达到的最小和
            int min_sum_this_iteration = i * 1;

            // j 代表用 i 个骰子想要凑成的目标和
            for (int j = min_sum_this_iteration; j <= max_sum_this_iteration; j++) {
                // 滑动窗口：new_dp[j] = dp[j-1] + dp[j-2] + ... + dp[j-k] (dp 指的是上一轮的dp)
                // 更新窗口和：
                // 1. 加入新进入窗口的项: dp[j-1] (对应当前骰子掷出1点，前i-1个骰子凑j-1)
                current_window_sum = (current_window_sum + dp[j - 1]) % MOD;
                if (j - 1 - k >= 0) { // 确保索引有效
                    current_window_sum = (current_window_sum - dp[j - 1 - k] + MOD) % MOD;
                }
                new_dp[j] = current_window_sum;
            }
            dp = new_dp;
        }

        return dp[target];
    }
};