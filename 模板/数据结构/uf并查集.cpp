#include "bits/stdc++.h"
using namespace std;
using ll = long long;

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

// 带权
class WeightedUnionFind {
public:
    std::vector<int> parent;
    std::vector<int> rank;
    std::vector<long long> weight;
    int count;

    explicit WeightedUnionFind(int n) : parent(n), rank(n), weight(n), count(n) {
        std::ranges::fill(rank, 1);
        std::ranges::fill(weight, 0LL);
        std::iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) {
            int px = parent[x];
            int r = find(px);
            weight[x] += weight[px];
            parent[x] = r;
        }
        return parent[x];
    }

    bool unite(int x, int y, long long w) {
        int rx = find(x);
        int ry = find(y);

        if (rx == ry) {
            return (weight[y] - weight[x] == w);
        }

        if (rank[rx] == rank[ry]) {
            parent[rx] = ry;
            rank[ry] += 1;
            weight[rx] = weight[y] - weight[x] - w;
        } else if (rank[rx] > rank[ry]) {
            parent[ry] = rx;
            weight[ry] = w + weight[x] - weight[y];
        } else {
            parent[rx] = ry;
            weight[rx] = weight[y] - weight[x] - w;
        }

        count--;
        return true;
    }

    bool same(int x, int y) { return find(x) == find(y); }

    long long diff(int x, int y) {
        return weight[y] - weight[x];
    }
};
