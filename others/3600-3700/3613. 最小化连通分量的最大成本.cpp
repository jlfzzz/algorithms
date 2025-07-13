#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> DIRS = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
constexpr int MOD = int(1e9 + 7);


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
    int minCost(int n, vector<vector<int>> &edges, int k) {

        if (k >= n) {
            return 0;
        }

        int lo = INT_MAX;
        int hi = 0;
        for (auto &e : edges) {
            lo = min(lo, e[2]);
            hi = max(hi, e[2]);
        }

        auto check = [&](int limit)->bool {
            UnionFind uf(n);
            for (auto &e : edges) {
                if (e[2] <= limit) {
                    uf.unite(e[0], e[1]);
                }
            }
            return uf.count <= k;
            };

        hi += 1;
        int ans = hi;
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