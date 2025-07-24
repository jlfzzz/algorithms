//
// Created by 123 on 25-6-3.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	int maxCandies(vector<int> &status, vector<int> &candies, vector<vector<int> > &keys,
				   vector<vector<int> > &containedBoxes, vector<int> &initialBoxes) {
		if (initialBoxes.size() == 0) {
			return 0;
		}
		int n = status.size();
		int ans = 0;
		vector<bool> opened(n, false);
		vector<bool> haveKey(n, false);
		vector<bool> haveContainedBoxes(n, false);

		queue<int> q;

		// 处理初始盒子
		for (int x: initialBoxes) {
			haveContainedBoxes[x] = true;
			if (status[x] == 1 || haveKey[x]) {
				q.push(x);
			}
		}

		while (!q.empty()) {
			int x = q.front();
			q.pop();

			if (opened[x]) continue;  // 已经打开过了

			// 检查是否可以打开这个盒子
			if (status[x] == 1 || haveKey[x]) {
				opened[x] = true;
				ans += candies[x];

				// 获得钥匙
				for (int key: keys[x]) {
					haveKey[key] = true;
					if (haveContainedBoxes[key] && !opened[key]) {
						q.push(key);
					}
				}

				// 获得包含的盒子
				for (int box: containedBoxes[x]) {
					if (!haveContainedBoxes[box]) {
						haveContainedBoxes[box] = true;
						if ((status[box] == 1 || haveKey[box]) && !opened[box]) {
							q.push(box);
						}
					}
				}
			}
		}
		return ans;
	}
};
