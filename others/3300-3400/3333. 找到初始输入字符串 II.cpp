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

using namespace std;

class Solution {
public:
    int possibleStringCount(string word, int k) {
        int n = word.length();
        if (n < k) { // 无法满足要求
            return 0;
        }

        const int MOD = 1'000'000'007;
        vector<int> cnts;
        long long ans = 1;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt++;
            if (i == n - 1 || word[i] != word[i + 1]) {
                // 如果 cnt = 1，这组字符串必选，无需参与计算
                if (cnt > 1) {
                    if (k > 0) { // 保证空间复杂度为 O(k)
                        cnts.push_back(cnt - 1);
                    }
                    ans = ans * cnt % MOD;
                }
                k--; // 注意这里把 k 减小了
                cnt = 0;
            }
        }

        if (k <= 0) {
            return ans;
        }

        vector<int> f(k);
        f[0] = 1;
        for (int c : cnts) {
            // 原地计算 f 的前缀和
            for (int j = 1; j < k; j++) {
                f[j] = (f[j] + f[j - 1]) % MOD;
            }
            // 计算子数组和
            for (int j = k - 1; j > c; j--) {
                f[j] = (f[j] - f[j - c - 1]) % MOD;
            }
        }

        ans -= reduce(f.begin(), f.end(), 0LL);
        return (ans % MOD + MOD) % MOD; // 保证结果非负
    }
};