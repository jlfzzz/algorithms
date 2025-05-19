#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int perfectMenu(vector<int> &materials, vector<vector<int>> &cookbooks, vector<vector<int>> &attribute, int limit) {
        int cookN = cookbooks.size();
        int materialN = materials.size();
        int ans = -1; // 初始化为-1，表示无法满足条件
        auto dfs = [&](this auto &&dfs, int index, int delicious, int full) -> void {
            if (index == cookN) {
                if (full >= limit) {
                    ans = max(ans, delicious);
                }
                return;
            }

            // 不选当前菜品
            dfs(index + 1, delicious, full);

            // 尝试选当前菜品
            bool canCook = true;
            // 检查材料是否足够
            for (int i = 0; i < materialN; ++i) {
                if (materials[i] < cookbooks[index][i]) {
                    canCook = false;
                    break;
                }
            }

            if (canCook) {
                // 消耗材料
                for (int i = 0; i < materialN; ++i) {
                    materials[i] -= cookbooks[index][i];
                }
                // 递归处理下一道菜
                dfs(index + 1, delicious + attribute[index][0], full + attribute[index][1]);
                // 回溯，恢复材料
                for (int i = 0; i < materialN; ++i) {
                    materials[i] += cookbooks[index][i];
                }
            }
            };

        dfs(0, 0, 0);
        return ans;
    }
};