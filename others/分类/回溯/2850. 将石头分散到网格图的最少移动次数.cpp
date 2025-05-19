#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>

using namespace std;

class Solution {
public:
    int minimumMoves(vector<vector<int>> &grid) {
        int ans = 100000;
        vector<vector<int>> have;
        vector<vector<int>> zero;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (grid[i][j] == 0) {
                    zero.push_back({ i,j });
                } else if (grid[i][j] > 1) {
                    have.push_back({ i, j, grid[i][j] - 1 });
                }
            }
        }

        int n = zero.size();
        auto dfs = [&](auto this &&dfs, int idx, int move) ->void {
            if (idx == n) {
                ans = min(ans, move);
                return;
            }

            int row = zero[idx][0];
            int col = zero[idx][1];

            for (auto &v : have) {
                if (v[2] > 0) {
                    v[2] -= 1;
                    int distance = abs(v[0] - row) + abs(v[1] - col);
                    dfs(idx + 1, move + distance);
                    v[2] += 1;
                }
            }
            };
        dfs(0, 0);
        return ans;
    }
};