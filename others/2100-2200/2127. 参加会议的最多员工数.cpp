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
	int maximumInvitations(vector<int>& favorite) {
		int n = favorite.size();
		vector<int> deg(n);
		for (int x : favorite) {
			deg[x]++;
		}

		queue<int> q;
		vector<int> dis(n, 1);
		for (int i = 0; i < n; i++) {
			if (deg[i] == 0) {
				q.push(i);
			}
		}

		while (!q.empty()) {
			int curr = q.front();
			q.pop();
			int x = favorite[curr];
			dis[x] = max(dis[x], dis[curr] + 1);
			if (--deg[x] == 0) {
				q.push(x);
			}
		}

		int ans_ring = 0, ans_chain = 0;
		for (int i = 0; i < n; i++) {
			if (deg[i] == 0) {
				continue;
			}
			deg[i] = 0;
			int count = 1;
			for (int x = favorite[i]; x != i; x = favorite[x]) {
				count++;
				deg[x] = 0;
			}

			if (count == 2) {
				ans_chain += dis[favorite[i]] + dis[i];
			} else {
				ans_ring = max(ans_ring, count);
			}
		}
		return max(ans_ring, ans_chain);
	}
};

class Solution {
public:
	int maximumInvitations(vector<int> &favorite) {
		int n = favorite.size();
		vector<int> deg(n);
		for (int x : favorite) {
			deg[x]++;
		}

		vector<int> max_depth(n, 1);
		queue<int> q;
		for (int i = 0; i < n; i++) {
			if (deg[i] == 0) {
				q.push(i);
			}
		}
		while (!q.empty()) {
			int x = q.front();
			q.pop();
			int y = favorite[x];
			max_depth[y] = max_depth[x] + 1;
			if (--deg[y] == 0) {
				q.push(y);
			}
		}

		int max_ring_size = 0, sum_chain_size = 0;
		for (int i = 0; i < n; i++) {
			if (deg[i] == 0) {
				continue;
			}

			deg[i] = 0;
			int ring_size = 1;
			for (int x = favorite[i]; x != i; x = favorite[x]) {
				deg[x] = 0;
				ring_size++;
			}

			if (ring_size == 2) { // 基环长度为 2
				sum_chain_size += max_depth[i] + max_depth[favorite[i]]; // 累加两条最长链的长度
			} else {
				max_ring_size = max(max_ring_size, ring_size); // 取所有基环长度的最大值
			}
		return max(max_ring_size, sum_chain_size);
		}
	}
};