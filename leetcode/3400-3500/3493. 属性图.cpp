#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <ranges>
#include <numeric>
#include <unordered_set>
#include <cmath>   
#include <memory> 
#include <map>
#include <queue>
#include <cstring>
#include <array> 
#include <bitset>
#include <stack>

using namespace std;

class UnionFind {
    vector<int> fa;

public:
    int cc; // 连通块个数

    UnionFind(int n) : fa(n), cc(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x == y) {
            return;
        }
        fa[x] = y;
        cc--;
    }
};

class Solution {
public:
    int numberOfComponents(vector<vector<int>> &properties, int k) {
        int n = properties.size();
        vector<unordered_set<int>> sets(n);
        for (int i = 0; i < n; i++) {
            sets[i] = unordered_set(properties[i].begin(), properties[i].end());
        }

        UnionFind uf(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int cnt = 0;
                for (int x : sets[j]) {
                    if (sets[i].contains(x)) {
                        cnt++;
                    }
                }
                if (cnt >= k) {
                    uf.merge(i, j);
                }
            }
        }
        return uf.cc;
    }
};