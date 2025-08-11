//
// Created by 123 on 25-6-15.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class LcaBinaryLifting {
public:
	vector<int> depth;
	vector<long long> dis;
	vector<vector<int> > pa;

	LcaBinaryLifting(vector<vector<int> > &edges) {
		int n = edges.size() + 1;
		int m = bit_width((unsigned) n);
		vector<vector<pair<int, int> > > g(n);
		for (auto &e: edges) {
			int x = e[0], y = e[1], w = e[2];
			g[x].emplace_back(y, w);
			g[y].emplace_back(x, w);
		}

		depth.resize(n);
		dis.resize(n);
		pa.resize(n, vector<int>(m, -1));

		auto dfs = [&](this auto &&dfs, int x, int fa) -> void {
			pa[x][0] = fa;
			for (auto &[y, w]: g[x]) {
				if (y != fa) {
					depth[y] = depth[x] + 1;
					dis[y] = dis[x] + w;
					dfs(y, x);
				}
			}
		};
		dfs(0, -1);

		for (int i = 0; i < m - 1; i++) {
			for (int x = 0; x < n; x++) {
				if (int p = pa[x][i]; p != -1) {
					pa[x][i + 1] = pa[p][i];
				}
			}
		}
	}

	int get_kth_ancestor(int node, int k) {
		for (int i = 0; i < bit_width((unsigned) k); ++i) {
			if (k >> i & 1) {
				node = pa[node][i];
			}
		}
		return node;
	}

	int get_lca(int x, int y) {
		if (depth[x] > depth[y]) {
			swap(x, y);
		}

		y = get_kth_ancestor(y, depth[y] - depth[x]);
		if (x == y) {
			return x;
		}

		for (int i = pa[x].size() - 1; i >= 0; --i) {
			int px = pa[x][i], py = pa[y][i];
			if (px != py) {
				x = px;
				y = py;
			}
		}

		return pa[x][0];
	}

	long long get_dis(int x, int y) {
		return dis[x] + dis[y] - dis[get_lca(x, y) * 2];
	}

	int upto_dis(int x, long long d) {
		long long dx = dis[x];
		for (int i = pa[x].size() - 1; i >= 0; --i) {
			int p = pa[x][i];
			if (p != -1 && dx - dis[p] <= d) {
				x = p;
			}
		}
		return x;
	}
};
