//
// Created by 123 on 25-6-4.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	bool canVisitAllRooms(vector<vector<int>>& rooms) {
		int n = rooms.size();
		vector<bool> visited(n, false);

		queue<int> q;
		q.emplace(0);
		visited[0] = true;
		int added = 1;
		while (!q.empty()) {
			int room = q.front();
			q.pop();
			for (int x : rooms[room]) {
				if (!visited[x]) {
					added++;
					visited[x] = true;
					q.emplace(x);
				}
			}
		}
		return added == n;
	}
};