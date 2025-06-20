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
    int sumOfPower(vector<int> &nums, int k) {
        vector<long long> f(k + 1);
        f[0] = 1;
        for (int x : nums) {
            for (int j = k; j >= 0; j--) {
                f[j] = (f[j] * 2 + (j >= x ? f[j - x] : 0)) % 1'000'000'007;
            }
        }
        return f[k];
    }
};


class Solution {
public:
    // dp[i][j][c]的含义是前i个子串，和是j且长度为k的 个数
    // 第i个选：i+1 j c = i j-nums[i] c-1
    // 第i个不选：i+1 j c = i j c
    int dp[105][105][105];
    int sumOfPower(vector<int> &nums, int k) {
        memset(dp, 0, sizeof(dp));
        const int MOD = 1e9 + 7;
        int n = nums.size();
        for (int i = 0; i <= n; i++) {
            dp[i][0][0] = 1;
        }
        // wrong:dp[0][0][0] = 1;
        for (int i = 0; i < n; i++) {
            for (int c = i + 1; c > 0; c--) {
                for (int j = 0; j <= k; j++) {
                    // 不选 nums[i]
                    dp[i + 1][j][c] = dp[i][j][c];

                    // 选 nums[i]，如果能选
                    if (j >= nums[i]) {
                        dp[i + 1][j][c] = (dp[i + 1][j][c] + dp[i][j - nums[i]][c - 1]) % MOD;
                    }
                }
            }
        }

        int ans = 0;
        int pow2 = 1;
        for (int i = n; i > 0; i--) {
            ans = (ans + (long long)dp[n][k][i] * pow2) % MOD;
            pow2 = pow2 * 2 % MOD;
        }
        return ans;
    }
};