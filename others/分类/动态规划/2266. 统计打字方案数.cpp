#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

// 创建最长连续字符串出现的长度的长度的vector

class Solution {
public:
    int countTexts(string pressedKeys) {
        long long ans = 1; // 使用 long long 来存储中间结果，避免乘法溢出
        int n = pressedKeys.size();
        int MOD = 1000000007;

        // 注意：这里的 vector 存储的是 int，但在计算新值时需要注意溢出
        vector<int> f(3);
        vector<int> g(4);
        f[0] = g[0] = 1; // 按 1 次
        f[1] = g[1] = 2; // 按 2 次
        f[2] = g[2] = 4; // 按 3 次
        g[3] = 8;        // 按 4 次 ('7' 或 '9')

        int i = 0;
        // right 指针不需要每次都重置为0，它应该紧跟 i
        while (i < n) {
            char c = pressedKeys[i];
            int right = i; // right 指针应该从当前 i 开始
            while (right < n && pressedKeys[right] == c) right++;
            int count = right - i; // 当前连续字符块的长度

            if (c == '7' || c == '9') {
                if (g.size() >= count) {
                    // 使用 long long 防止 ans * g[...] 溢出
                    ans = (ans * g[count - 1]) % MOD;
                } else {
                    int size = g.size();
                    // 注意：这里的 more 计算的是需要新增的元素个数，循环次数应该是 more
                    int more = count - size;
                    g.reserve(count); // 预分配空间可能提高效率
                    for (int k = 0; k < more; k++) { // 循环变量避免与外层 i 冲突，使用 k
                        // 计算新值时使用 long long 防止加法溢出
                        long long next_g = ((long long)g[size + k - 1] + g[size + k - 2] + g[size + k - 3] + g[size + k - 4]) % MOD;
                        g.push_back((int)next_g); // 添加新计算的值
                    }
                    // 使用 long long 防止 ans * g[...] 溢出
                    ans = (ans * g[count - 1]) % MOD;
                }
            } else {
                if (f.size() >= count) {
                    // 使用 long long 防止 ans * f[...] 溢出
                    ans = (ans * f[count - 1]) % MOD;
                } else {
                    int size = f.size();
                    int more = count - size;
                    f.reserve(count);
                    for (int k = 0; k < more; k++) { // 循环变量避免与外层 i 冲突，使用 k
                        // 计算新值时使用 long long 防止加法溢出
                        long long next_f = ((long long)f[size + k - 1] + f[size + k - 2] + f[size + k - 3]) % MOD;
                        f.push_back((int)next_f); // 添加新计算的值
                    }
                    // 使用 long long 防止 ans * f[...] 溢出
                    ans = (ans * f[count - 1]) % MOD;
                }
            }

            i = right; // 更新 i 到下一个块的开始
        }
        // 最后结果转回 int
        return (int)ans;
    }
};


class Solution {
public:
    int countTexts(string pressedKeys) {
        int n = pressedKeys.size();
        const int MOD = 1000000007;

        // 查找连续相同字符的最大长度，以确定需要的dp数组大小
        int maxLen = 1;
        int currLen = 1;
        for (int i = 1; i < n; i++) {
            if (pressedKeys[i] == pressedKeys[i - 1]) {
                currLen++;
            } else {
                maxLen = max(maxLen, currLen);
                currLen = 1;
            }
        }
        maxLen = max(maxLen, currLen);

        // 动态分配dp数组大小
        vector<int> dp1(maxLen + 1, 0); // 对应2,3,4,5,6,8按键
        vector<int> dp2(maxLen + 1, 0); // 对应7,9按键

        // 初始化
        dp1[0] = dp2[0] = 1;
        dp1[1] = dp2[1] = 1;

        if (maxLen >= 2) {
            dp1[2] = dp2[2] = 2;
        }

        if (maxLen >= 3) {
            dp1[3] = dp2[3] = 4;
        }

        // 计算所需的dp值
        for (int i = 4; i <= maxLen; i++) {
            dp1[i] = ((long long)dp1[i - 1] + dp1[i - 2] + dp1[i - 3]) % MOD;
            dp2[i] = ((long long)dp2[i - 1] + dp2[i - 2] + dp2[i - 3] + dp2[i - 4]) % MOD;
        }

        // 计算结果
        long long ans = 1;
        int count = 1;

        for (int i = 0; i < n - 1; i++) {
            if (pressedKeys[i] == pressedKeys[i + 1]) {
                count++;
            } else {
                int currentDp = (pressedKeys[i] != '7' && pressedKeys[i] != '9') ?
                    dp1[count] : dp2[count];
                ans = (ans * currentDp) % MOD;
                count = 1;
            }
        }

        // 处理最后一组字符
        int lastDp = (pressedKeys.back() != '7' && pressedKeys.back() != '9') ?
            dp1[count] : dp2[count];
        ans = (ans * lastDp) % MOD;

        return ans;
    }
};
