#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> choose;

        auto dfs = [&](this auto &&dfs, int start, int sum) {
            // 终止条件：已选k个数
            if (choose.size() == k) {
                if (sum == n) {
                    ans.emplace_back(choose);
                }
                return;
            }

            // 遍历可能的数字
            for (int i = start; i <= 9; i++) {
                // 剪枝：如果当前和已经超过目标，提前结束
                if (sum + i > n) {
                    break;
                }
                choose.push_back(i);  // 选择当前数字i
                dfs(i + 1, sum + i); // 递归处理下一个数字
                choose.pop_back();    // 回溯
            }
            };

        dfs(1, 0);
        return ans;
    }
};