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
    /**
     * @brief 计算使 nums 成为非递减顺序所需操作数的最小值。
     *
     * @param nums 一个只包含 1, 2, 3 的整数 vector。
     * @return int 所需的最小操作数（删除次数）。
     */
    int minimumOperations(std::vector<int> &nums) {
        int n = nums.size();

        // dp1: 以 1 结尾的最长非递减子序列长度
        // dp2: 以 2 结尾的最长非递减子序列长度
        // dp3: 以 3 结尾的最长非递减子序列长度
        int dp1 = 0;
        int dp2 = 0;
        int dp3 = 0;

        for (int num : nums) {
            if (num == 1) {
                // 只能延长纯 1 的子序列
                dp1++;
                // 按照之前的逻辑，遇到 1 时，dp2 和 dp3 保持不变，
                // 因为 1 不能直接延长以 2 或 3 结尾的序列。
                // 但为了保持状态转移的完整性（即使值不变），可以写作：
                // dp2 = max(dp1, dp2); // 这实际上不会增加 dp2
                // dp3 = max({dp1, dp2, dp3}); // 这实际上也不会增加 dp3
                // 最简洁且正确的更新方式是只更新 dp1
            } else if (num == 2) {
                // 可以接在以 1 结尾的序列后面，或接在以 2 结尾的序列后面
                // 更新以 2 结尾的最长子序列长度
                dp2 = std::max(dp1, dp2) + 1;
                // 同样，为了保持状态转移完整性，可以写作：
               // dp3 = max({dp1, dp2, dp3}); // 这实际上不会增加 dp3
               // 最简洁的方式是只更新 dp2
            } else { // num == 3
                // 可以接在以 1, 2 或 3 结尾的序列后面
                // 更新以 3 结尾的最长子序列长度
                dp3 = std::max({ dp1, dp2, dp3 }) + 1;
            }
            // 注意：在每个数字处理完后，dp1, dp2, dp3 代表的是当前为止
            // 分别以 1, 2, 3 结尾的最长非递减子序列的长度。
        }

        // 最终的最长非递减子序列的长度是 dp1, dp2, dp3 中的最大值
        int max_length = std::max({ dp1, dp2, dp3 });

        // 需要删除的元素数量 = 总数 - 最长非递减子序列长度
        return n - max_length;
    }
};


class Solution {
public:
    int minimumOperations(vector<int> &nums) {
        int n = nums.size();
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            auto it = ranges::upper_bound(ans, x);
            if (it == ans.end()) {
                ans.emplace_back(x);
            } else {
                *it = x;
            }
        }
        return n - ans.size();
    }
};
