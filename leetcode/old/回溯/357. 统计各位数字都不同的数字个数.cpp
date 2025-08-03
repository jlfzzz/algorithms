#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>

using namespace std;

// 2 数学解法

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;

        int ans = 0;
        vector<bool> used(10, false);

        function<void(int, int)> dfs = [&](int depth, int limit) {
            if (depth == limit) {
                ans++;
                return;
            }

            for (int i = 0; i < 10; ++i) {
                if (used[i]) continue;
                if (depth == 0 && i == 0) continue; // 不允许前导0

                used[i] = true;
                dfs(depth + 1, limit);
                used[i] = false;
            }
            };

        ans = 1; // 0 的情况

        for (int len = 1; len <= n; ++len) {
            dfs(0, len);
        }

        return ans;
    }
};

// 需要累加，位数不同的分别算，最后加起来
// 例如两位， 第一位不能选0，剩下9，第二位剩下9个可以选的，所以是9x9

class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) return 1;
        int ans = 10;
        for (int i = 2, last = 9; i <= n; i++) {
            int cur = last * (10 - i + 1);
            ans += cur; last = cur;
        }
        return ans;
    }
};
