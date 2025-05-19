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
    int minPathCost(vector<vector<int>> &grid, vector<vector<int>> &moveCost) {
        int m = grid.size(), n = grid[0].size();
        vector f(m, vector<int>(n, INT_MAX));
        f[m - 1] = grid[m - 1];
        for (int i = m - 2; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) { // 移动到下一行的第 k 列
                    f[i][j] = min(f[i][j], f[i + 1][k] + moveCost[grid[i][j]][k]);
                }
                f[i][j] += grid[i][j];
            }
        }
        return ranges::min(f[0]);
    }
};