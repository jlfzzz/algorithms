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
#include <bitset>
#include <stack>
#include <set>
#include <random>

using namespace std;


class Solution {
public:
    int smallestIndex(vector<int> &nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            int sum = 0;
            while (x > 0) {
                sum += x % 10;
                x /= 10;
            }
            if (sum == i) {
                return i;
            }
        }
        return -1;
    }
};


class Solution {
public:
    // 辅助函数：计算数字的数位和
    int digitSum(int num) {
        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int> &nums) {
        int n = nums.size();

        // 创建一个包含原始值、数位和和原始位置的数组
        vector<tuple<int, int, int>> arr; // <原始值, 数位和, 原始位置>
        for (int i = 0; i < n; i++) {
            arr.push_back({ nums[i], digitSum(nums[i]), i });
        }

        // 根据数位和和原始值排序
        sort(arr.begin(), arr.end(), [](const auto &a, const auto &b) {
            if (get<1>(a) != get<1>(b)) {
                return get<1>(a) < get<1>(b); // 按数位和升序
            }
            return get<0>(a) < get<0>(b); // 如果数位和相同，按原始值升序
            });

        // 记录每个位置上应该放的元素的原始位置
        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[i] = get<2>(arr[i]);
        }

        // 计算最小交换次数
        int swaps = 0;
        for (int i = 0; i < n; i++) {
            // 如果当前位置元素不在正确位置上
            if (pos[i] != i) {
                // 找到应该在当前位置的元素，与其交换
                while (pos[i] != i) {
                    swap(pos[i], pos[pos[i]]);
                    swaps++;
                }
            }
        }

        return swaps;
    }
};

class Solution {
public:
    int direction[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    int minMoves(vector<string> &matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        unordered_map<char, pair<pair<int, int>, pair<int, int>>> doors;
        unordered_map<char, bool> used;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] != '.' && matrix[i][j] != '#') {
                    if (doors.count(matrix[i][j])) {
                        doors[matrix[i][j]].second = { i, j };
                    } else {
                        doors[matrix[i][j]] = { {i, j}, {i, j} };
                        used[matrix[i][j]] = false;
                    }
                }
            }
        }
        vector<vector<int>> memo(n + 1, vector<int>(m + 1, -1));
        for (int i = 0; i < n; i++) {
            memo[i + 1][0] = INT_MAX;
        }
        for (int i = 0; i < m; i++) {
            memo[0][i + 1] = INT_MAX;
        }
        memo[0][0] = INT_MAX;

        // 添加访问标记数组
        vector<vector<bool>> visited(n + 1, vector<bool>(m + 1, false));

        auto dfs = [&](auto &&dfs, int x, int y, int step) -> int {
            if (x == n && y == m) {
                if (memo[x][y] == -1 || step < memo[x][y]) {
                    memo[x][y] = step;
                }
                return memo[x][y];
            }
            if (memo[x][y] != -1) {
                return memo[x][y];
            }
            if (matrix[x - 1][y - 1] == '#') {
                return INT_MAX;
            }

            // 标记当前位置为已访问
            visited[x][y] = true;

            int res = INT_MAX;
            for (int i = 0; i < 4; i++) {
                int nx = x + direction[i][0];
                int ny = y + direction[i][1];
                if (nx > 0 && nx <= n && ny > 0 && ny <= m && !visited[nx][ny]) {
                    res = min(res, dfs(dfs, nx, ny, step + 1));
                }
            }
            if (matrix[x - 1][y - 1] != '.' && !used[matrix[x - 1][y - 1]]) {
                used[matrix[x - 1][y - 1]] = true;
                int new_x, new_y;
                char c = matrix[x - 1][y - 1];
                if (x - 1 == doors[c].first.first && y - 1 == doors[c].first.second) {
                    new_x = doors[c].second.first + 1;
                    new_y = doors[c].second.second + 1;
                } else {
                    new_x = doors[c].first.first + 1;
                    new_y = doors[c].first.second + 1;
                }
                if (!visited[new_x][new_y]) {
                    res = min(res, dfs(dfs, new_x, new_y, step));
                }
                used[matrix[x - 1][y - 1]] = false;
            }

            // 回溯，将当前位置标记为未访问
            visited[x][y] = false;

            memo[x][y] = res;
            return res;
            };

        dfs(dfs, 1, 1, 0);
        return memo[n][m] == INT_MAX ? -1 : memo[n][m];
    }
};



