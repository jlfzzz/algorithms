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
    int findIntegers(int n) {
        string s = "";
        int temp_n = n;
        if (temp_n == 0) s = "0";
        else {
            while (temp_n > 0) {
                s = (temp_n % 2 == 0 ? '0' : '1') + s;
                temp_n /= 2;
            }
        }

        int len = s.size();
        vector<int> dp(len + 1, -1);

        auto dfs = [&](this auto &&dfs, int idx, bool isLimit, bool isOne) -> int {
            if (idx == len) {
                return 1;
            }

            if (!isLimit && !isOne && dp[idx] != -1) return dp[idx];

            int hi = isLimit ? s[idx] - '0' : 1;

            int count = 0;
            for (int i = 0; i <= hi; i++) {
                if (i == 1 && isOne) continue;

                count += dfs(idx + 1, isLimit && i == (s[idx] - '0'), i == 1);
            }

            if (!isLimit && !isOne) dp[idx] = count;

            return count;
            };

        return dfs(0, true, false);
    }
};






















class Solution {
public:
    int findIntegers(int n) {
        // 1. 将 n 转换为二进制字符串 (LSB 在 index 0)
        string s = "";
        int temp_n = n;
        if (temp_n == 0) s = "0"; // 处理 n = 0 的情况
        else {
            while (temp_n > 0) {
                s += (temp_n % 2 == 0 ? '0' : '1');
                temp_n /= 2;
            }
        }

        int len = s.length();

        // 2. 定义 DP 状态和记忆化数组
        // dp[idx][meetLimit][prevOne]
        // idx: 当前处理的位数索引 (从 len-1 即 MSB 向 0 即 LSB 处理)
        // meetLimit: bool, 是否受 n 的当前位限制
        // prevOne: bool, 前一位（更高位）是否是 1
        vector<vector<vector<int>>> dp(len, vector<vector<int>>(2, vector<int>(2, -1)));

        // 3. 定义 DFS 函数
        // idx 从 len-1 (MSB) 递减到 -1
        function<int(int, bool, bool)> dfs =
            [&](int idx, bool meetLimit, bool prevOne) -> int {
            // Base case: 所有位都处理完毕 (索引越过最低位)
            if (idx < 0) {
                return 1; // 找到一个有效组合
            }

            // 检查记忆化
            // 注意：只有在非 meetLimit 状态下才能复用结果
            if (!meetLimit && dp[idx][meetLimit][prevOne] != -1) {
                return dp[idx][meetLimit][prevOne];
            }

            int count = 0;
            // 确定当前位的上界
            // 因为 s[idx] 已经是正确的位（从高到低处理），直接使用
            int limit = meetLimit ? (s[idx] - '0') : 1;

            // 遍历当前位可以取的数字 digit (0 或 1)
            for (int digit = 0; digit <= limit; ++digit) {
                // 检查连续 1 的约束
                if (prevOne && digit == 1) {
                    continue; // 不能连续两个 1
                }

                // 递归到下一位 (更低位)
                count += dfs(idx - 1, meetLimit && (digit == limit), digit == 1);
            }

            // 存储结果 (仅当非 meetLimit 时)
            if (!meetLimit) {
                dp[idx][meetLimit][prevOne] = count;
            }

            return count;
            };

        // 4. 初始调用 DFS
        // 从最高位 (index len - 1) 开始，初始受限 (meetLimit=true)，前一位看作 0 (prevOne=false)
        return dfs(len - 1, true, false);
    }
};