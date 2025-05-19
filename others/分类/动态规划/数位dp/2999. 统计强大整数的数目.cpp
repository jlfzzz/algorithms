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
不受上下界约束的情况 (!is_low && !is_high 或 is_tight = false):
    当递归到达一个状态，后续数字的选择不再受到原始边界 start 或 finish (或 n 在 count(n) 方法中) 的具体数值限制时，意味着从当前位置 idx 开始，有多少种合法的构造方式只取决于 idx 本身、剩余的位数、全局限制（如 limit）以及其他固定规则（如后缀 s）。

    无论我们是通过哪条路径（即选择了哪些前面的数字）到达这个 (idx, false, false) 或 (idx, false) 的状态，只要状态参数相同，后续能构造出的合法数字数量 一定是相同的。

    因此，这个计算结果是通用的，可以安全地存储（记忆化）并直接复用，避免了大量重复计算。

受上下界约束的情况 (is_low = true 或 is_high = true 或 is_tight = true):
    当递归状态仍然受到某个边界的约束时，当前位可以取的数字范围会受到 start_s[idx] 或 finish_s[idx] (或 n[idx]) 的限制。
    这意味着 dfs(idx, true, ...) 或 dfs(idx, ..., true) 的计算结果是特定于当前这个边界值的。如果换一个边界值（比如在计算 count(start-1) 时），即使 idx 相同，is_tight=true 状态下的计算结果也可能不同。

    所以，这种受限状态下的计算结果通常不能像非受限状态那样简单地用 dp[idx] 或 memo[idx][false] 来存储并跨边界值复用。如果需要对它们进行记忆化，就需要包含 is_low/is_high/is_tight 标志的更完整的状态 memo[idx][is_low][is_high] 或 memo[idx][is_tight]，并且要注意这种记忆化只在同一次 count_powerful(n_val) 调用内部有效（对于 is_tight=true 状态）。
*/

// 第一种 一维dp，只存储 非触碰到上下限的
// 第二种 三维dp 全部存储，理论不会有重复计算

class Solution {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        string start_s = to_string(start);
        string finish_s = to_string(finish);
        int len = finish_s.size();
        start_s = string(len - start_s.size(), '0') + start_s;
        int suffix_len = s.size();
        vector<long long> dp(20, -1);

        auto dfs = [&](this auto &&dfs, int index, bool is_low, bool is_high) -> long long {
            if (index == len) {
                return 1;
            }

            if (len - index <= suffix_len) {
                int suffix_index = suffix_len - (len - index);
                char suffix_char = s[suffix_index];
                if (is_low && suffix_char < start_s[index]) return 0;
                if (is_high && suffix_char > finish_s[index]) return 0;

                return dfs(index + 1, is_low && suffix_char == start_s[index], is_high && suffix_char == finish_s[index]);
            }

            if (!is_high && !is_low && dp[index] != -1) return dp[index];

            int lo = is_low ? start_s[index] - '0' : 0;
            int hi = is_high ? finish_s[index] - '0' : 9;

            long long count = 0;
            for (int d = lo; d <= min(hi, limit); d++) {
                count += dfs(index + 1, is_low && d == lo, is_high && d == hi);
            }

            if (!is_high && !is_low) dp[index] = count;

            return count;
            };
        return dfs(0, true, true);
    }
};


class Solution {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        string start_s = to_string(start);
        string finish_s = to_string(finish);
        int len = finish_s.size();
        start_s = string(len - start_s.size(), '0') + start_s; // 补齐前导零
        int suffix_len = s.size();

        // 三维记忆化数组：memo[index][is_low][is_high]
        vector<vector<vector<long long>>> memo(
            len,
            vector<vector<long long>>(2, vector<long long>(2, -1))
        );

        function<long long(int, bool, bool)> dfs = [&](int index, bool is_low, bool is_high) -> long long {
            // Base case: 所有位都处理完了
            if (index == len) {
                return 1;
            }

            // 处理后缀部分
            if (len - index <= suffix_len) {
                int suffix_index = suffix_len - (len - index);
                char suffix_char = s[suffix_index];
                if (is_low && suffix_char < start_s[index]) return 0;
                if (is_high && suffix_char > finish_s[index]) return 0;

                return dfs(index + 1, is_low && suffix_char == start_s[index], is_high && suffix_char == finish_s[index]);
            }

            // 检查记忆化数组
            if (memo[index][is_low][is_high] != -1) {
                return memo[index][is_low][is_high];
            }

            // 计算当前位可填的数字范围
            int lo = is_low ? start_s[index] - '0' : 0;
            int hi = is_high ? finish_s[index] - '0' : 9;

            long long count = 0;
            for (int d = lo; d <= min(hi, limit); d++) {
                count += dfs(index + 1, is_low && d == lo, is_high && d == hi);
            }

            // 存储结果到记忆化数组
            memo[index][is_low][is_high] = count;
            return count;
            };

        return dfs(0, true, true);
    }
};




class Solution {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        // 计算[start,finish]范围内，满足条件的数字数量
        string startStr = to_string(start - 1); // 减1处理左边界
        string finishStr = to_string(finish);

        if (start <= 1) startStr = "0"; // 特殊情况处理

        // 如果s长度大于数字长度，无解
        if (s.size() > finishStr.size()) return 0;

        vector<long long> dp1(20, -1); // 确保足够大
        vector<long long> dp2(20, -1);

        auto dfs = [&](this auto &&dfs, int pos, bool isLimit, bool isNum, const string &bound, const vector<long long> &dp) -> long long {
            // 已经处理完所有位置
            if (pos == bound.size()) {
                return isNum ? 1 : 0; // 只有形成了有效数字才计数
            }

            // 当前位置是后缀s对应的位置
            if (bound.size() - pos <= s.size()) {
                // 检查当前位置是否可以匹配s对应位置
                int sPos = s.size() - (bound.size() - pos);
                int digit = s[sPos] - '0';

                // 如果当前数字限制小于后缀要求，或者后缀数字超过limit，无解
                if ((isLimit && (bound[pos] - '0') < digit) || digit > limit) {
                    return 0;
                }

                // 继续检查下一位
                return dfs(pos + 1, isLimit && (bound[pos] - '0' == digit), true, bound, dp);
            }

            // 如果不受限且已计算过，直接返回
            if (!isLimit && isNum && dp[pos] != -1) return dp[pos];

            long long res = 0;

            // 如果当前没有形成有效数字，可以跳过（保持前导零）
            if (!isNum) {
                res += dfs(pos + 1, false, false, bound, dp);
            }

            // 当前位可以选择的数字范围
            int start = isNum ? 0 : 1; // 前导零处理
            int end = isLimit ? (bound[pos] - '0') : 9;
            end = min(end, limit);

            for (int d = start; d <= end; d++) {
                res += dfs(pos + 1, isLimit && d == (bound[pos] - '0'), true, bound, dp);
            }

            // 存储结果
            if (!isLimit && isNum) {
                const_cast<vector<long long> &>(dp)[pos] = res;
            }

            return res;
            };

        // 计算[0,finish]中的答案
        long long countFinish = dfs(0, true, false, finishStr, dp2);

        // 计算[0,start-1]中的答案
        long long countStart = 0;
        if (s.size() <= startStr.size()) {
            countStart = dfs(0, true, false, startStr, dp1);
        }

        return countFinish - countStart;
    }
};