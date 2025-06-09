//
// Created by 123 on 25-6-1.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


class Solution {
public:
	void union_(vector<int> &uf, int a, int b) {
		uf[find(uf, a)] = uf[find(uf, b)];
	}

	int find(vector<int> &uf, int x) {
		if (uf[x] != x) {
			uf[x] = find(uf, uf[x]);
		}
		return uf[x];
	}

	int minSwapsCouples(vector<int> &row) {
		int n = row.size();
		int m = n / 2;
		vector<int> uf(m);
		for (int i = 0; i < m; i++) {
			uf[i] = i;
		}
		for (int i = 0; i < n; i += 2) {
			union_(uf, row[i] / 2, row[i + 1] / 2);
		}
		int cnt = 0;

		for (int i = 0; i < m; i++) {
			if (i == find(uf, i)) {
				cnt++;
			}
		}
		return m - cnt;
	}
};
