//
// Created by 123 on 25-5-30.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int closestMeetingNode(vector<int>& edges, int node1, int node2) {
		int n = edges.size();
		auto helper = [&](int node) -> vector<int> {
			vector<int> ret(n, n);
			int dis = 0;
			ret[node] = 0;
			while (edges[node] != -1 && edges[node] != n) {
				edges[node] = ++dis;
			}
			return ret;
		};

		auto v1 = helper(node1);
		auto v2 = helper(node2);
		int ans = -1;
		int mx = 0;
		for (int i = 0; i < n; i++) {
			int d = max(v1[i], v2[i]);
			if (d < mx) {
				mx = d;
				ans = i;
			}
		}
		return ans;
	}
};



class Solution {
public:
	int closestMeetingNode(vector<int>& edges, int node1, int node2) {
		int n = edges.size();
		auto calc_dis = [&](int x) {
			vector<int> dis(n, n); // 初始化成 n，表示无法到达或者尚未访问的节点
			// 从 x 出发，直到无路可走（x=-1）或者重复访问节点（dis[x]<n）
			for (int d = 0; x >= 0 && dis[x] == n; x = edges[x]) {
				dis[x] = d++;
			}
			return dis;
		};

		vector<int> dis1 = calc_dis(node1);
		vector<int> dis2 = calc_dis(node2);

		int min_dis = n, ans = -1;
		for (int i = 0; i < n; i++) {
			int d = max(dis1[i], dis2[i]);
			if (d < min_dis) {
				min_dis = d;
				ans = i;
			}
		}
		return ans;
	}
};