//
// Created by 123 on 25-7-6.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

class UnionFind {
public:
    vector<int> parent;
    vector<int> rank;
    int count;

    explicit UnionFind(const int n) : count(n) {
        parent.resize(n);
        rank.resize(n);
        ranges::fill(rank, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);

        if (root_x == root_y) {
            return false;
        }

        if (rank[root_x] == rank[root_y]) {
            parent[root_x] = root_y;
            rank[root_y] += 1;
        } else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
        } else {
            parent[root_x] = root_y;
        }
        count--;
        return true;
    }
};

class Solution {
public:
    int minTime(int n, vector<vector<int>> &edges, int k) {
        int lo = 0;
        int hi = 1e9 + 10000;
        int ans = hi - 1;


        auto check = [&](int t)->bool {
            UnionFind uf(n);
            for (auto &v : edges) {
                int a = v[0];
                int b = v[1];
                int time = v[2];
                if (time > t) {
                    uf.unite(a, b);
                }
            }
            return uf.count >= k;
            };


        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (check(mid)) {
                ans = mid;
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};