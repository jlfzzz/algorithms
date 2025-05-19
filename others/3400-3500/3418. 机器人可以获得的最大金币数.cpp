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
    int maximumAmount(vector<vector<int>> &coins) {
        int m = coins.size(), n = coins[0].size();
        vector f(m + 1, vector(n + 1, array<int, 3>{INT_MIN / 2, INT_MIN / 2, INT_MIN / 2}));
        f[0][1] = { 0, 0, 0 };
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int x = coins[i][j];
                f[i + 1][j + 1][0] = max(f[i + 1][j][0], f[i][j + 1][0]) + x;
                f[i + 1][j + 1][1] = max({ f[i + 1][j][1] + x, f[i][j + 1][1] + x,
                                          f[i + 1][j][0], f[i][j + 1][0] });
                f[i + 1][j + 1][2] = max({ f[i + 1][j][2] + x, f[i][j + 1][2] + x,
                                          f[i + 1][j][1], f[i][j + 1][1] });
            }
        }
        return f[m][n][2];
    }
};
