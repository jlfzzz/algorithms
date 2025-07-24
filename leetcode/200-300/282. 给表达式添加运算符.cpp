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

using namespace std;

// a + b * c, b 是 prev，前一步已经加过它了，所以先 减prev 再 + prev * curr_num

class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> ans;
        int n = num.size();
        long long target_val = target; // 使用 long long 以防 target 较大或计算中溢出

        if (n == 0) {
            return ans;
        }

        // 定义 DFS lambda 函数
        // 参数: index, path, current_eval, prev_term
        function<void(int, string, long long, long long)> dfs =
            [&](int index, string path, long long current_eval, long long prev_term) {

            // 基本情况：已经处理完所有数字
            if (index == n) {
                if (current_eval == target_val) {
                    ans.push_back(path); // 如果当前表达式值等于目标值，添加到结果
                }
                return;
            }

            long long current_num = 0; // 当前正在构建的数字的值
            string current_num_str;   // 当前正在构建的数字的字符串形式

            // 从 index 开始，尝试构建一个或多个数字的数
            for (int i = index; i < n; ++i) {
                // 处理前导零：如果当前数字长度大于1且以'0'开头，则无效
                if (i > index && num[index] == '0') {
                    break;
                }

                current_num_str += num[i];
                current_num = stoll(current_num_str); // 转换为 long long

                if (index == 0) {
                    // 如果是表达式的第一个数，没有前置运算符
                    // 直接将数字加入路径，递归调用
                    // current_eval 和 prev_term 都设为第一个数的值
                    dfs(i + 1, current_num_str, current_num, current_num);
                } else {
                    // 如果不是第一个数，可以尝试添加 '+', '-', '*'

                    // 尝试 '+'
                    // 新的 current_eval = 旧 current_eval + current_num
                    // 新的 prev_term = current_num
                    dfs(i + 1, path + "+" + current_num_str, current_eval + current_num, current_num);

                    // 尝试 '-'
                    // 新的 current_eval = 旧 current_eval - current_num
                    // 新的 prev_term = -current_num (注意符号)
                    dfs(i + 1, path + "-" + current_num_str, current_eval - current_num, -current_num);

                    // 尝试 '*'
                    // 新的 current_eval = 旧 current_eval - prev_term + (prev_term * current_num)
                    //      (撤销上一步加/减 prev_term 的效果，然后加上乘积)
                    // 新的 prev_term = prev_term * current_num (因为这个乘积是下一轮运算的'上一项')
                    dfs(i + 1, path + "*" + current_num_str, current_eval - prev_term + (prev_term * current_num), prev_term * current_num);
                }
            }
            };

        // 初始调用 DFS
        // 从索引 0 开始，初始路径为空，初始计算值为 0，初始上一项也为 0
        dfs(0, "", 0, 0);

        return ans;
    }
};