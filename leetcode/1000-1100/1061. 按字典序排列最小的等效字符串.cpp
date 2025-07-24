//
// Created by 123 on 25-6-5.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class UnionFind {
public:
	vector<int> parent;
	UnionFind() {
		parent.resize(26);
		for (int i = 0; i < 26; i++) {
			parent[i] = i;
		}
	}

	void unite(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);

		if (rootX < rootY) {
			parent[rootY] = rootX;
		} else if (rootX > rootY) {
			parent[rootX] = rootY;
		}
	}

	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}
};

class Solution {
public:
	string smallestEquivalentString(string s1, string s2, string baseStr) {
		int n = s1.length();
		UnionFind uf;
		for (int i = 0; i < n; i++) {
			uf.unite(s1[i] - 'a', s2[i] - 'a');
		}

		int m = baseStr.length();
		for (int i = 0; i < m; i++) {
			baseStr[i] = uf.find(baseStr[i] - 'a') + 'a';
		}
		return baseStr;
	}
};