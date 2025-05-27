#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
    int maximumMinutes(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> fire_time(n, vector<int>(m, INT_MAX));
        queue<pair<int, int>> q;

        // 1. 预处理火势蔓延时间
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    q.emplace(i, j);
                    fire_time[i][j] = 0;
                }
            }
        }
        int t = 0;
        while (!q.empty()) {
            int sz = q.size();
            t++;
            for (int i = 0; i < sz; i++) {
                auto [x, y] = q.front(); q.pop();
                for (auto& d : DIR) {
                    int nx = x + d[0], ny = y + d[1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0 && fire_time[nx][ny] == INT_MAX) {
                        fire_time[nx][ny] = t;
                        q.emplace(nx, ny);
                    }
                }
            }
        }

        // 2. 检查等待wait分钟后能否到达终点
        auto check = [&](int wait) -> bool {
            if (fire_time[0][0] <= wait) return false; // 起点就被烧了
            vector<vector<int>> vis(n, vector<int>(m, -1));
            queue<tuple<int, int, int>> q;
            q.emplace(0, 0, wait);
            vis[0][0] = wait;
            while (!q.empty()) {
                auto [x, y, t] = q.front(); q.pop();
                if (x == n-1 && y == m-1) {
                    // 终点可以和火同时到达
                    return t <= fire_time[x][y];
                }
                for (auto& d : DIR) {
                    int nx = x + d[0], ny = y + d[1];
                    int nt = t + 1;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 0) {
                        if (nt < fire_time[nx][ny] && (vis[nx][ny] == -1 || nt < vis[nx][ny])) {
                            vis[nx][ny] = nt;
                            q.emplace(nx, ny, nt);
                        }
                        // 终点可以和火同时到达
                        if (nx == n-1 && ny == m-1 && nt == fire_time[nx][ny]) return true;
                    }
                }
            }
            return false;
        };

        // 3. 二分最大等待时间
        int lo = 0, hi = n * m + 5, ans = -1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid;
            }
        }
        return ans > m * n + 3 ? 1e9 : ans;
    }
};