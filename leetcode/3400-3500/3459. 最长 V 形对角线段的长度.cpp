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

class Solution {
    static constexpr int DIRS[4][2] = { {1, 1}, {1, -1}, {-1, -1}, {-1, 1} };

public:
    int lenOfVDiagonal(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        vector memo(m, vector<array<array<int, 2>, 4>>(n));

        auto dfs = [&](this auto &&dfs, int i, int j, int k, bool can_turn, int target) -> int {
            i += DIRS[k][0];
            j += DIRS[k][1];
            if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != target) {
                return 0;
            }
            int &res = memo[i][j][k][can_turn]; // 注意这里是引用
            if (res) { // 之前计算过
                return res;
            }
            res = dfs(i, j, k, can_turn, 2 - target); // 直行
            if (can_turn) {
                res = max(res, dfs(i, j, (k + 1) % 4, false, 2 - target)); // 右转
            }
            return ++res; // 算上当前位置
            };

        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    for (int k = 0; k < 4; k++) { // 枚举起始方向
                        ans = max(ans, dfs(i, j, k, true, 2) + 1);
                    }
                }
            }
        }
        return ans;
    }
};
