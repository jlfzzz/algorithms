#include <bits/stdc++.h>
using namespace std;
using pll = pair<long long, long long>;
#define i128 __int128_t
#define ull unsigned long long
constexpr int inf = 0x3f3f3f3f / 2;
using pii = pair<int, int>;
using ll = long long;


class Solution {
public:
    int minMoves(vector<string> &classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sx, sy;
        int cnt = 0;
        vector<vector<int>> grid(m, vector<int>(n, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sx = i;
                    sy = j;
                } else if (classroom[i][j] == 'L') {
                    grid[i][j] = cnt++;
                }
            }
        }

        int u = (1 << cnt) - 1;
        vector<vector<vector<int>>> visited(m, vector<vector<int>>(n, vector<int>(1 << cnt, -1)));
        queue<tuple<int, int, int, int, int>> q;

        q.push({sx, sy, 0, energy, 0});
        visited[sx][sy][0] = energy;

        int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!q.empty()) {
            auto [r, c, mask, e, steps] = q.front();
            q.pop();

            if (mask == u) {
                return steps;
            }

            int ne = e;
            if (classroom[r][c] == 'R') {
                ne = energy;
            }

            if (ne == 0)
                continue;

            for (auto &d: dirs) {
                int nr = r + d[0];
                int nc = c + d[1];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n || classroom[nr][nc] == 'X') {
                    continue;
                }

                int nMask = mask;
                if (classroom[nr][nc] == 'L') {
                    if (grid[nr][nc] != -1) {
                        nMask |= (1 << grid[nr][nc]);
                    }
                }

                int nne = ne - 1;

                if (nne > visited[nr][nc][nMask]) {
                    visited[nr][nc][nMask] = nne;
                    q.push({nr, nc, nMask, nne, steps + 1});
                }
            }
        }

        return -1;
    }
};
