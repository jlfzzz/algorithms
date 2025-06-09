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
	int minimizedMaximum(int n, vector<int>& quantities) {
		// 判定问题
		auto check = [&](int x) -> bool{
			// 计算所需商店数量的最小值，并与商店数量进行比较
			int cnt = 0;
			for (int q: quantities){
				cnt += (q - 1) / x + 1;
			}
			return cnt <= n;
		};

		int l = 1, r = *max_element(quantities.begin(), quantities.end()) + 1;
		int ans = 0;
		// 二分查找寻找最小的使得判定问题为真的 x
		while (l < r){
			int mid = l + (r - l) / 2;
			if (check(mid)){
				ans = mid;
				r = mid;
			}
			else{

				l = mid + 1;
			}
		}
		return ans;
	}
};