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

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> ans; // 存储最终结果
        vector<int> path;      // 存储当前构建的排列
        int n = nums.size();
        vector<bool> visited(n, false); // 标记 nums 中的元素是否已在当前 path 中

        // 1. 对 nums 进行排序，这是剪枝去重的关键前提
        sort(nums.begin(), nums.end());

        function<void(void)> dfs =
            [&]() -> void {
            // 基准条件：当路径长度等于 nums 大小时，找到一个完整排列
            if (path.size() == n) {
                ans.push_back(path);
                return;
            }

            // 遍历 nums 中的每个元素
            for (int i = 0; i < n; ++i) {
                // 剪枝条件 1：如果当前元素已被访问过，则跳过
                if (visited[i]) {
                    continue;
                }

                // 剪枝条件 2：去除重复排列的关键
                // - i > 0 确保 nums[i-1] 是有效的
                // - nums[i] == nums[i-1] 表示当前元素与前一个元素相同
                // - !visited[i-1] 表示前一个相同的元素 nums[i-1] 在 *当前* 的搜索层级中 *未被* 使用
                //   如果 nums[i-1] 未被使用（即它还在可选列表中），那么选择 nums[i] 会导致与
                //   后续（或之前）选择 nums[i-1] 时产生的排列重复。只有当 nums[i-1] 已经被
                //   加入到当前 path 中（即 visited[i-1] 为 true）时，我们才考虑使用 nums[i]。
                if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) {
                    continue;
                }

                // 选择当前元素 nums[i]
                visited[i] = true;
                path.push_back(nums[i]);

                // 递归进入下一层
                dfs();

                // 回溯：撤销选择
                path.pop_back();
                visited[i] = false;
            }
            };

        dfs(); // 启动 DFS
        return ans;
    }
};