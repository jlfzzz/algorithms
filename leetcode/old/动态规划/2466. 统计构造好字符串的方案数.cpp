#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        const int MOD = 1000000007; // 正确的模数值
        vector<int> dp(high + 1, 0);
        dp[0] = 1; // 空字符串算一种情况

        // 计算每个长度可能的字符串数量
        for (int i = 1; i <= high; i++) {
            // 添加零的情况
            if (i >= zero) {
                dp[i] = (dp[i] + dp[i - zero]) % MOD;
            }

            // 添加一的情况
            if (i >= one) {
                dp[i] = (dp[i] + dp[i - one]) % MOD;
            }
        }

        // 计算从low到high长度的总和
        int ans = 0;
        for (int i = low; i <= high; i++) {
            ans = (ans + dp[i]) % MOD;
        }

        return ans;
    }
};