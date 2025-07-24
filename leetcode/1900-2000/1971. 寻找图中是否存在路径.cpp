//
// Created by 32098 on 25-5-27.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class UnionFind {
public:
  vector<int> parent;
  vector<int> rank;
  explicit UnionFind(const int n) {
    parent = vector<int>(n);
    rank = vector<int>(n);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  void unite(const int x, const int y) {
    int fa_x = find(x);
    int fa_y = find(y);

    if (fa_x != fa_y) {
      if (rank[fa_x] > rank[fa_y]) {
        parent[fa_y] = fa_x;
      } else if (rank[fa_x] == rank[fa_y]) {
        parent[fa_y] = fa_x;
        rank[fa_x]++;
      } else {
        parent[fa_x] = fa_y;
      }
    }
  }

  int find(const int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }
};

class Solution {
public:
  bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
    UnionFind uf(n);
    for (auto& edge : edges) {
      uf.unite(edge[0], edge[1]);
    }
    return uf.find(destination) == uf.find(source);
  }
};

class Solution1 {
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
