#include "bits/stdc++.h"
using namespace std;

class Solution {
    static constexpr int DIRS[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

public:
    int trapRainWater(vector<vector<int>> &heightMap) {
        int m = heightMap.size(), n = heightMap[0].size();
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    pq.emplace(heightMap[i][j], i, j);
                    heightMap[i][j] = -1; // 标记 (i,j) 访问过
                }
            }
        }

        int ans = 0;
        while (!pq.empty()) {
            auto [min_height, i, j] = pq.top(); // min_height 是木桶的短板
            pq.pop(); // 去掉短板
            for (auto &[dx, dy]: DIRS) {
                int x = i + dx, y = j + dy; // (i,j) 的邻居
                if (0 <= x && x < m && 0 <= y && y < n && heightMap[x][y] >= 0) { // (x,y) 没有访问过
                    // 如果 (x,y) 的高度小于 min_height，那么接水量为 min_height - heightMap[x][y]
                    ans += max(min_height - heightMap[x][y], 0);
                    // 给木桶新增一块高为 max(min_height, heightMap[x][y]) 的木板
                    pq.emplace(max(min_height, heightMap[x][y]), x, y);
                    heightMap[x][y] = -1; // 标记 (x,y) 访问过
                }
            }
        }
        return ans;
    }
};
