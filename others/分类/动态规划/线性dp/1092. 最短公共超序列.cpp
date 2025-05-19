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

using namespace std;

class Solution {
public:
    string shortestCommonSupersequence(string &s, string &t) {
        // f[i+1][j+1] 表示 s 的前 i 个字母和 t 的前 j 个字母的最短公共超序列的长度
        int n = s.length(), m = t.length(), f[n + 1][m + 1];
        for (int j = 0; j <= m; ++j) f[0][j] = j; // 递归边界
        for (int i = 1; i <= n; ++i) f[i][0] = i; // 递归边界
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (s[i] == t[j]) // 最短公共超序列一定包含 s[i]
                    f[i + 1][j + 1] = f[i][j] + 1;
                else // 取更短的组成答案
                    f[i + 1][j + 1] = min(f[i][j + 1], f[i + 1][j]) + 1;

        string ans;
        int i = n - 1, j = m - 1;
        while (i >= 0 && j >= 0) {
            if (s[i] == t[j]) { // 公共超序列一定包含 s[i]
                ans += s[i];
                --i;
                --j; // 相当于继续递归 make_ans(i - 1, j - 1)
            } else if (f[i + 1][j + 1] == f[i][j + 1] + 1)
                ans += s[i--]; // 相当于继续递归 make_ans(i - 1, j)
            else
                ans += t[j--]; // 相当于继续递归 make_ans(i, j - 1)
        }
        reverse(ans.begin(), ans.end());
        // 补上前面的递归边界
        return s.substr(0, i + 1) + t.substr(0, j + 1) + ans;
    }
};
