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

using namespace std;

class Solution {
    // 使用一个大的整数常量表示无穷大
    static constexpr int inf = 0x3f3f3f3f;
public:
    int minSideJumps(vector<int> &obstacles) {
        int n = obstacles.size() - 1; // 总共有 n+1 个点，从 0 到 n

        // dp[i][j] = 到达点 i 处，第 j 条跑道 (0-indexed) 所需的最小侧跳次数
        vector<vector<int>> dp(n + 1, vector<int>(3, inf));

        // 初始化第 0 个点的情况
        // 题目规定从点 0 的跑道 2 (索引为 1) 出发
        dp[0][1] = 0;
        // 在点 0 处可以跳到跑道 1 (索引 0) 或跑道 3 (索引 2)，需要 1 次侧跳
        dp[0][0] = 1;
        dp[0][2] = 1;

        // 迭代处理从点 1 到点 n
        for (int i = 1; i <= n; ++i) {
            int min_jumps_at_i = inf; // 到达点 i 处任意 *有效* 跑道的最小跳跃次数（在考虑点 i 处的侧跳 *之前*）

            // 步骤 1：从上一个点 (i-1) 转移状态，并计算 min_jumps_at_i
            for (int j = 0; j < 3; ++j) {
                // 检查当前点 i 的第 j+1 条跑道是否有障碍物
                if (obstacles[i] == j + 1) {
                    // 有障碍物，无法到达 dp[i][j]
                    dp[i][j] = inf;
                } else {
                    // 没有障碍物，可以直接从 dp[i-1][j] 过来
                    dp[i][j] = dp[i - 1][j];
                    // 更新到达点 i 的最小跳跃次数（不考虑在 i 点的侧跳）
                    min_jumps_at_i = min(min_jumps_at_i, dp[i][j]);
                }
            }

            // 步骤 2：考虑在点 i 处进行侧跳
            // 如果可以通过 min_jumps_at_i 次跳跃到达点 i 的某条跑道，
            // 那么就可以通过 min_jumps_at_i + 1 次跳跃到达点 i 处 *任何其他没有障碍物* 的跑道 k。
            for (int j = 0; j < 3; ++j) {
                // 检查当前点 i 的第 j+1 条跑道是否有障碍物
                if (obstacles[i] != j + 1) {
                    // 比较直接过来的成本 dp[i][j] 和 从点 i 的其他跑道跳过来的成本 (min_jumps_at_i + 1)
                    dp[i][j] = min(dp[i][j], min_jumps_at_i + 1);
                }
            }
        }

        // 最终结果是到达点 n 处，三条跑道中所需最小的侧跳次数
        return *min_element(dp[n].begin(), dp[n].end());
    }
};

// 0-1 BFS

class Solution {
public:
    int minSideJumps(vector<int> &obstacles) {
        int n = obstacles.size(), dis[n][3];
        memset(dis, 0x3f, sizeof(dis));
        dis[0][1] = 0;
        deque<pair<int, int>> q;
        q.emplace_back(0, 1); // 起点
        for (;;) {
            auto [i, j] = q.front(); q.pop_front();
            int d = dis[i][j];
            if (i == n - 1) return d; // 到达终点
            if (obstacles[i + 1] != j + 1 && d < dis[i + 1][j]) { // 向右
                dis[i + 1][j] = d;
                q.emplace_front(i + 1, j); // 加到队首
            }
            for (int k : {(j + 1) % 3, (j + 2) % 3}) // 枚举另外两条跑道（向上/向下）
                if (obstacles[i] != k + 1 && d + 1 < dis[i][k]) {
                    dis[i][k] = d + 1;
                    q.emplace_back(i, k); // 加到队尾
                }
        }
    }
}; 