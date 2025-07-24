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
    int countSymmetricIntegers(int low, int high) {
        string low_s = to_string(low), high_s = to_string(high);
        int n = high_s.size(), m = n / 2;
        int diff_lh = n - low_s.size();

        // dfs 中的 start <= diff_lh，-9m <= diff <= 9m
        vector memo(n, vector(diff_lh + 1, vector<int>(m * 18 + 1, -1)));
        auto dfs = [&](this auto &&dfs, int i, int start, int diff, bool limit_low, bool limit_high) -> int {
            if (i == n) {
                return diff == m * 9;
            }

            // start 当 is_num 用
            if (start != -1 && !limit_low && !limit_high && memo[i][start][diff] != -1) {
                return memo[i][start][diff];
            }

            int lo = limit_low && i >= diff_lh ? low_s[i - diff_lh] - '0' : 0;
            int hi = limit_high ? high_s[i] - '0' : 9;

            // 如果前面没有填数字，且剩余数位个数是奇数，那么当前数位不能填数字
            if (start < 0 && (n - i) % 2) {
                // 如果必须填数字（lo > 0），不合法，返回 0
                return lo > 0 ? 0 : dfs(i + 1, start, diff, true, false);
            }

            int res = 0;
            bool is_left = start < 0 || i < (start + n) / 2;
            for (int d = lo; d <= hi; d++) {
                res += dfs(i + 1,
                    start < 0 && d > 0 ? i : start, // 记录第一个填数字的位置
                    diff + (is_left ? d : -d), // 左半 +，右半 -
                    limit_low && d == lo,
                    limit_high && d == hi);
            }

            if (start != -1 && !limit_low && !limit_high) {
                memo[i][start][diff] = res;
            }
            return res;
            };

        // 初始化 diff = m * 9，避免出现负数导致 memo 下标越界
        return dfs(0, -1, m * 9, true, true);
    }
};

















class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        int ans = 0;
        for (int i = low; i <= high; i++) {
            string s = to_string(i);
            int n = s.size();
            if (n % 2 == 0 && reduce(s.begin(), s.begin() + n / 2) == reduce(s.begin() + n / 2, s.end())) {
                ans++;
            }
        }
        return ans;
    }
};