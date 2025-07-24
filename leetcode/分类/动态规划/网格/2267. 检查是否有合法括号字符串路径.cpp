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

// 3是对的，但std：：pair没有哈希，不能用set存。
// 2 可以改成只存 ---->>> c = 左括号计数 - 右括号计数 且必须永远大于等于0， 逻辑一样，没快多少
// 4 最快， 并且快很多很多很多 （100倍）

struct ArrayHash {
    std::size_t operator()(const std::array<int, 2> &a) const {
        std::size_t h1 = std::hash<int>{}(a[0]);
        std::size_t h2 = std::hash<int>{}(a[1]);
        // Simple hash combination (or use a better one like boost::hash_combine)
        return h1 ^ (h2 << 1);
    }
};

class Solution {
public:
    bool hasValidPath(vector<vector<char>> &grid) {
        // Initial check remains the same
        if (grid[0][0] == ')') return false;

        int n = grid.size();
        int m = grid[0].size();

        // Modify dp declaration to use unordered_set<array<int, 2>, ArrayHash>
        vector<vector<unordered_set<array<int, 2>, ArrayHash>>> dp(n + 1, vector<unordered_set<array<int, 2>, ArrayHash>>(m + 1));

        // Initialize with array using braced initialization {left_count, right_count}
        // Assuming the state represents {open_parentheses_count, close_parentheses_count}
        dp[1][1].insert({ 1, 0 }); // Starting at (0,0) with '(', count is {1, 0}

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // Skip the starting cell as it's initialized
                if (i == 1 && j == 1) continue;

                char curr = grid[i - 1][j - 1];
                // Determine the change in counts based on the current character
                int currLeft = (curr == '(' ? 1 : 0);
                int currRight = (curr == ')' ? 1 : 0);

                // Process states coming from the left (dp[i][j-1])
                if (j > 1) { // Check if left neighbor exists
                    for (const auto &p : dp[i][j - 1]) {
                        int prevLeft = p[0];  // Access using array index [0]
                        int prevRight = p[1]; // Access using array index [1]
                        // Check validity: closed count cannot exceed open count *at any point*
                        // This check should ideally happen *before* adding the current char's effect,
                        // but based on your original logic, we apply it after calculating potential new state.
                        int potentialNewLeft = prevLeft + currLeft;
                        int potentialNewRight = prevRight + currRight;
                        if (potentialNewRight <= potentialNewLeft) {
                            dp[i][j].insert({ potentialNewLeft, potentialNewRight });
                        }
                    }
                }


                // Process states coming from the top (dp[i-1][j])
                if (i > 1) { // Check if top neighbor exists
                    for (const auto &p : dp[i - 1][j]) {
                        int prevLeft = p[0];  // Access using array index [0]
                        int prevRight = p[1]; // Access using array index [1]
                        int potentialNewLeft = prevLeft + currLeft;
                        int potentialNewRight = prevRight + currRight;
                        // Check validity
                        if (potentialNewRight <= potentialNewLeft) {
                            dp[i][j].insert({ potentialNewLeft, potentialNewRight });
                        }
                    }
                }
            }
        }

        // Check the final states at the destination (n, m)
        for (const auto &p : dp[n][m]) {
            // A valid path requires the total open count to equal the total closed count
            if (p[0] == p[1]) return true;
        }

        return false; // No valid path found
    }
};

class Solution {
public:
    bool hasValidPath(vector<vector<char>> &grid) {
        if (grid[0][0] == ')') return false; // 起点不能是 ')'

        int n = grid.size();
        int m = grid[0].size();

        // dp[i][j] 存储到达格子 (i-1, j-1) 时所有可能的有效平衡度 c
        vector<vector<unordered_set<int>>> dp(n + 1, vector<unordered_set<int>>(m + 1));

        // 初始化起点：处理完 (0,0) 处的 '(' 后，平衡度为 1
        dp[1][1].insert(1);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                // 跳过已初始化的起点
                if (i == 1 && j == 1) continue;

                char curr = grid[i - 1][j - 1];
                int delta = (curr == '(' ? 1 : -1);

                // 合并来自上方 (dp[i-1][j]) 的状态
                if (i > 1) {
                    for (int prev_c : dp[i - 1][j]) {
                        int new_c = prev_c + delta;
                        if (new_c >= 0) { // 检查新平衡度是否有效
                            // 剪枝：如果 new_c 过大，后续不可能降为 0 (类似 DFS 中的剪枝)
                            // 剩余格子数 = (n - i) + (m - j)
                            if (new_c <= (n - i) + (m - j) + 1) { // +1 是因为终点前必须是1
                                dp[i][j].insert(new_c);
                            }
                        }
                    }
                }

                // 合并来自左方 (dp[i][j-1]) 的状态
                if (j > 1) {
                    for (int prev_c : dp[i][j - 1]) {
                        int new_c = prev_c + delta;
                        if (new_c >= 0) { // 检查新平衡度是否有效
                            // 剪枝
                            if (new_c <= (n - i) + (m - j) + 1) {
                                dp[i][j].insert(new_c);
                            }
                        }
                    }
                }
            }
        }

        // 检查终点 (n, m) 是否可以达到平衡度 0
        // 注意：这里的 dp[n][m] 存储的是到达 (n-1, m-1) 的平衡度。
        // 题目要求的是路径有效，即最终平衡为 0。
        // 由于终点 grid[n-1][m-1] 必须是 ')' 才能使平衡度最终为 0，
        // 那么到达终点格子 *之前* 的平衡度必须是 1，并且终点格子是 ')'。
        // 这个DP状态记录的是处理完 grid[i-1][j-1] *之后* 的平衡度。
        // 所以我们需要检查 dp[n][m] 中是否存在 0。
        return dp[n][m].count(0);
    }
};



class Solution {
public:
    bool hasValidPath(vector<vector<char>> &grid) {
        if (grid[0][0] == ')') return false;

        int n = grid.size();
        int m = grid[0].size();
        vector<vector<unordered_set<pair<int, int>>>> dp(n + 1, vector<unordered_set<pair<int, int>>>(m + 1));
    
        dp[1][1].insert({ 1, 0 });

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (i == 1 && j == 1) continue;

                char curr = grid[i - 1][j - 1];
                int currRight = curr == ')' ? 1 : 0;
                int currLeft = curr == '(' ? 1 : 0;

                for (auto &p : dp[i][j - 1]) {
                    if (p.second + currRight <= p.first) {
                        dp[i][j].insert({ p.first + currLeft, p.second + currRight });
                    }
                }

                for (auto &p : dp[i - 1][j]) {
                    if (p.second + currRight <= p.first) {
                        dp[i][j].insert({ p.first + currLeft, p.second + currRight });
                    }
                }
            }
        }

        for (auto &p : dp[n][m]) {
            if (p.first == p.second) return true;
        }
        return false;
    }
};

class Solution {
public:
    bool hasValidPath(vector<vector<char>> &grid) {
        int m = grid.size();
        int n = grid[0].size();

        if ((m + n) % 2 == 0 || grid[0][0] == ')' || grid[m - 1][n - 1] == '(') {
            return false;
        }

        // --- 使用 vector 代替 VLA ---
        int max_c = (m + n + 1) / 2; // 计算第三维大小
        // 初始化为 m x n x max_c 的三维 vector，所有元素默认为 false
        vector<vector<vector<bool>>> vis(m, vector<vector<bool>>(n, vector<bool>(max_c, false)));

        function<bool(int, int, int)> dfs =
            // 现在 vis 是 vector，可以被 lambda 安全捕获
            [&](int x, int y, int c) -> bool {

            if (c > m - x + n - y - 1) {
                return false;
            }

            if (x == m - 1 && y == n - 1) {
                return c == 1;
            }

            // 边界检查 c，确保不会越界访问 vis 的第三维
            if (c < 0 || c >= max_c) {
                return false; // 平衡度超出合理范围
            }


            if (vis[x][y][c]) {
                return false;
            }
            vis[x][y][c] = true;

            int current_c = c + (grid[x][y] == '(' ? 1 : -1);

            // 检查 current_c 是否仍在有效范围内 (虽然递归调用前也会检查c>=0, 但这里更明确)
            // if (current_c < 0) return false; // 这一步其实包含在下面的 c>=0 判断中了

             // 注意：这里的 c 是进入 (x,y) 前的 c，传递给下一层的是 current_c
            return current_c >= 0 &&
                ((x < m - 1 && dfs(x + 1, y, current_c)) ||
                    (y < n - 1 && dfs(x, y + 1, current_c)));
            };

        return dfs(0, 0, 0); // 初始平衡度为 0
    }
};
