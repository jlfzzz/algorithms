//
// Created by 123 on 25-6-30.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

vector<int> z_func(string word) {
	int n = word.size();
	vector<int> z(n, 0);
	int left = 0;
	int right = 0;
	for (int i = 1; i < n; i++) {
		// 镜像。如果i<=right,证明当前在z_box里面
		// z_box[left, right] == word[0, right - left]，每个一一对应
		// 字符串: a b c a b c a b
		// 位置:   0 1 2 3 4 5 6 7
		//
		// 假设 Z-box = [3, 5]，表示 s[3..5] = s[0..2]
		// 即: "abc" = "abc"
		//
		// 位置对应关系：
		// s[3] ↔ s[0]  (3-3=0)
		// s[4] ↔ s[1]  (4-3=1)
		// s[5] ↔ s[2]  (5-3=2)
		//
		// 如果 i=4，那么镜像位置 = i-l = 4-3 = 1
		// s[1:2] == s[4:5]
		// 所以 s[4] 对应 s[1]，它们的值相同！
		// 直接取min(right - i + 1, z[i - left])
		if (i <= right) {
			z[i] = min(right - i + 1, z[i - left]);
		}
		while (i + z[i] < n && word[i + z[i]] == word[z[i]]) {
			left = i;
			right = i + z[i];
			z[i] += 1;
		}
	}
	return z;
}
