#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


class Solution {
public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses, vector<int>());
    vector<int> deg(numCourses, 0);
    for (auto& v : prerequisites) {
      graph[v[1]].emplace_back(v[0]);
      deg[v[0]]++;
    }

    queue<int> q;
    int added = 0;
    for (int i = 0; i < numCourses; ++i) {
      if (deg[i] == 0) {
        q.push(i);
        added++;
      }
    }

    while (!q.empty()) {
      int size = q.size();
      for (int i = 0; i < size; ++i) {
        int father = q.front();
        q.pop();
        for (int neighbour : graph[father]) {
          deg[neighbour]--;
          if (deg[neighbour] == 0) {
            q.push(neighbour);
            added++;
          }
        }
      }
    }
    return added == numCourses;
  }
};
