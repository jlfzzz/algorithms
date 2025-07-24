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

/*
将一个数字表示成幂的和的方案数

给你两个 正 整数 n 和 x 。

请你返回将 n 表示成一些 互不相同 正整数的 x 次幂之和的方案数。换句话说，你需要返回互不相同整数 [n1, n2, ..., nk] 的集合数目，满足 n = n1x + n2x + ... + nkx 。

由于答案可能非常大，请你将它对 10^9 + 7 取余后返回。

比方说，n = 160 且 x = 3 ，一个表示 n 的方法是 n = 2^3 + 3^3 + 5^3 。
*/

class Solution {
public:
    int numberOfWays(int n, int x) {
        vector<long long> dp(n + 1, 0);
        dp[1] = 1;
        dp[0] = 1;

        for (int i = 2; i <= n; i++) {
            if (pow(i, x) > n) {
                break;
            }
            for (int j = n; j >= i; j--) {
                if (j - pow(i, x) >= 0) {
                    dp[j] += (dp[j - pow(i, x)] % 1000000007);
                }
            }
        }

        return dp[n] % 1000000007;
    }
};

class Solution {
public:
    int numberOfWays(int n, int x) {
        int MOD = 1000000007;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        // 初始化为0不需要这两个for
        // 如果是-1就要
        // for (int i = 0;i <= n; i++) {
        //     dp[i][0] = 1;
        // }

        // for (int i = 1;i <= n; i++) {
        //     dp[0][i] = 0;
        // }
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= n;j++) {
                dp[i][j] = dp[i - 1][j]; // 不选当前的

                if (pow(i, x) <= j) {
                    // 初始化为0，所以如果没储存，加了也不影响
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - pow(i, x)]) % MOD;   // “储存了才能加”
                }
            }
        }

        long long ans = 0;
        for (auto &v : dp) {
            ans = (ans + v[n] != -1 ? v[n] : 0);
        }
        return ans % MOD;
    }
};