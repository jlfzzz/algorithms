//
// Created by 123 on 25-5-31.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int snakesAndLadders(vector<vector<int>>& board) {
		int n = board.size();
		vector<int8_t> vis(n * n + 1);
		vis[1] = true; // 题目保证起点没有蛇梯，不写也可以
		vector<int> q = {1}; // 起点
		for (int step = 0; !q.empty(); step++) {
			auto tmp = q;
			q.clear();
			for (int x : tmp) {
				if (x == n * n) { // 终点
					return step;
				}
				for (int y = x + 1; y <= min(x + 6, n * n); y++) {
					int r = (y - 1) / n, c = (y - 1) % n;
					if (r % 2) {
						c = n - 1 - c; // 奇数行从右到左
					}
					int nxt = board[n - 1 - r][c];
					if (nxt < 0) {
						nxt = y;
					}
					if (!vis[nxt]) {
						vis[nxt] = true; // 有环的情况下，避免死循环
						q.push_back(nxt);
					}
				}
			}
		}
		return -1; // 无法到达终点
	}
};




















class Solution {
public:
	int snakesAndLadders(vector<vector<int>>& board) {
		int n = board.size();
		vector<int8_t> vis(n * n + 1);
		vis[1] = true; // 题目保证起点没有蛇梯，不写也可以
		vector<int> q = {1}; // 起点
		for (int step = 0; !q.empty(); step++) {
			auto tmp = q;
			q.clear();
			for (int x : tmp) {
				if (x == n * n) { // 终点
					return step;
				}
				for (int y = x + 1; y <= min(x + 6, n * n); y++) {
					int r = (y - 1) / n, c = (y - 1) % n;
					if (r % 2) {
						c = n - 1 - c; // 奇数行从右到左
					}
					int nxt = board[n - 1 - r][c];
					if (nxt < 0) {
						nxt = y;
					}
					if (!vis[nxt]) {
						vis[nxt] = true; // 有环的情况下，避免死循环
						q.push_back(nxt);
					}
				}
			}
		}
		return -1; // 无法到达终点
	}
};