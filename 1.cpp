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

// 正确答案是solution，但这题目是傻逼。
//  应该return vector<string> 考察 超级大数还差不多

class Solution {
  static constexpr int DIRS[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

public:
  int minMoves(vector<string> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    deque<pair<int, int>> dq;
    dq.emplace_back(0, 0);
    vector<vector<pair<int, int>>> record(26, vector<pair<int, int>>());

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (isupper(matrix[i][j])) {
          record[matrix[i][j] - 'A'].emplace_back(i, j);
        }
      }
    }

    vector<vector<int>> memo(n, vector<int>(m, -1));
    memo[0][0] = 0;
    while (!dq.empty()) {
      auto &[x, y] = dq.front();
      dq.pop_front();
      int curr = memo[x][y];
      char c = matrix[x][y];

      if (x == n - 1 && y == m - 1) {
        return curr;
      }


      if (isupper(c)) {
        for (auto &[new_x, new_y]: record[c - 'A']) {
          dq.emplace_back(new_x, new_y);
          memo[new_x][new_y] = curr;
        }
        record[c - 'A'].clear();
      }

      for (auto &dir: DIRS) {
        int new_x = x + dir[0];
        int new_y = y + dir[1];
        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < m && matrix[new_x][new_y] != '#') {
          memo[new_x][new_y] = curr + 1;
          dq.emplace_back(new_x, new_y);
        }
      }
    }
    return -1;
  }
};
