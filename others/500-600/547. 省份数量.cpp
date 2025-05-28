//
// Created by 123 on 25-5-26.
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

  explicit UnionFind(int n) {
    parent = vector<int>(n);
    rank = vector<int>(n);
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  void unite(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x == root_y) return;

    if (rank[root_x] < rank[root_y]) {
      parent[root_x] = root_y;
    } else if (rank[root_x] > rank[root_y]) {
      parent[root_y] = root_x;
    } else {
      parent[root_x] = root_y;
      rank[root_y] += 1;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }
};

class Solution {
public:
  int findCircleNum(vector<vector<int>> &isConnected) {
    int n = isConnected.size();
    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (isConnected[i][j]) {
          uf.unite(i, j);
        }
      }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
     if (uf.parent[i] == i) {
       ans++;
     }
    }
    return ans;
  }
};

class Solution2 {
public:
  int Find(vector<int> &parent, int index) {
    if (parent[index] != index) {
      parent[index] = Find(parent, parent[index]);
    }
    return parent[index];
  }

  void Union(vector<int> &parent, int index1, int index2) { parent[Find(parent, index1)] = Find(parent, index2); }

  int findCircleNum(vector<vector<int>> &isConnected) {
    int cities = isConnected.size();
    vector<int> parent(cities);
    for (int i = 0; i < cities; i++) {
      parent[i] = i;
    }
    for (int i = 0; i < cities; i++) {
      for (int j = i + 1; j < cities; j++) {
        if (isConnected[i][j] == 1) {
          Union(parent, i, j);
        }
      }
    }
    int provinces = 0;
    for (int i = 0; i < cities; i++) {
      if (parent[i] == i) {
        provinces++;
      }
    }
    return provinces;
  }
};

class Solution1 {
public:
  int findCircleNum(vector<vector<int>> &isConnected) {
    int n = isConnected.size();
    vector<vector<int>> graph(n, vector<int>());
    vector<int> visited(n, false);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i != j && isConnected[i][j]) {
          graph[i].push_back(j);
          graph[j].push_back(i);
        }
      }
    }

    auto dfs = [&](this auto &&dfs, int child, int fa) -> void {
      if (visited[child])
        return;
      visited[child] = true;
      for (int neighbour: graph[child]) {
        if (neighbour != fa) {
          dfs(neighbour, child);
        }
      }
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (!visited[i]) {
        ans++;
        dfs(i, -1);
      }
    }
    return ans;
  }
};
