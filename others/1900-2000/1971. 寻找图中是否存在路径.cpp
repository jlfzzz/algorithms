//
// Created by 32098 on 25-5-27.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  bool validPath(int n, vector<vector<int>> &edges, int source, int destination) {
    vector<vector<int>> adj(n, vector<int>());
    for (auto &edge: edges) {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }

    vector<bool> visited(n, false);
    auto dfs = [&](this auto &&dfs, int curr, int fa) -> bool {
      if (visited[curr]) {
        return false;
      }
      if (curr == destination) {
        return true;
      }
      visited[curr] = true;
      bool ret = false;
      for (int neighbour: adj[curr]) {
        if (neighbour != fa)
          ret |= dfs(neighbour, curr);
      }
      return ret;
    };
    return dfs(source, -1);
  }
};
