//
// Created by 123 on 25-5-26.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// dfs和拓扑

class Solution2 {
public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses, vector<int>());
    for (auto& edge : prerequisites) {
      graph[edge[1]].push_back(edge[0]);
    }

    vector<int> visited(numCourses, 0);
    bool have_ring = false;
    auto dfs = [&](this auto&&dfs, int j) -> void {
      if (visited[j] == 1) {
        have_ring = true;
        return;
      }
      if (visited[j] == 2 || have_ring) {
        return;
      }
      visited[j] = 1;
      for (int neighbour : graph[j]) {
        dfs(neighbour);
      }
      visited[j] = 2;
    };
    for (int i = 0; i < numCourses; i++) {
      dfs(i);
      if (have_ring) {
        return !have_ring;
      }
    }
    return !have_ring;
  }
};

class Solution2 {
public:
  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses, vector<int>());
    vector<int> deg(numCourses, 0);
    for (auto& edge : prerequisites) {
      graph[edge[1]].push_back(edge[0]);
      deg[edge[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
      if (deg[i] == 0)
        q.push(i);
    }

    int visited = 0;
    while (!q.empty()) {
      ++visited;
      int u = q.front();
      q.pop();
      for (int neighbour : graph[u]) {
        --deg[neighbour];
        if (deg[neighbour] == 0) {
          q.push(neighbour);
        }
      }
    }
    return visited == numCourses;
  }
};