#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  static constexpr int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

  int minMoves(vector<string> &matrix) {
    int m = matrix.size(), n = matrix[0].size();
    if (matrix[m - 1][n - 1] == '#') {
      return -1;
    }

    vector<pair<int, int>> pos[26]{};
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        char c = matrix[i][j];
        if (isupper(c)) {
          pos[c - 'A'].emplace_back(i, j);
        }
      }
    }

    vector dis(m, vector<int>(n, INT_MAX));
    dis[0][0] = 0;
    deque<pair<int, int>> q{{0, 0}};

    while (!q.empty()) {
      auto [x, y] = q.front();
      q.pop_front();

      int d = dis[x][y];
      if (x == m - 1 && y == n - 1) {
        return d;
      }

      char c = matrix[x][y];
      if (c != '.') {
        for (auto &[px, py]: pos[c - 'A']) {
          if (px != x || py != y) {
            dis[px][py] = d;
            q.emplace_front(px, py);
          }
        }
        pos[c - 'A'].clear();
      }

      for (auto &[dx, dy]: DIRS) {
        int nx = x + dx, ny = y + dy;
        if (0 <= nx && nx < m && 0 <= ny && ny < n && matrix[nx][ny] != '#' && d + 1 < dis[nx][ny]) {
          dis[nx][ny] = d + 1;
          q.emplace_back(nx, ny);
        }
      }
    }
    return -1;
  }
};
