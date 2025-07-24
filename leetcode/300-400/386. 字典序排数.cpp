//
// Created by 123 on 25-6-8.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] =  {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
	vector<int> lexicalOrder(int n) {
		vector<int> ans(n);
		int curr = 1;
		for (int j = 0; j < n; ++j) {
			ans[j] = curr;
			if (curr * 10 <= n) {
				curr *= 10;
			} else {
				while (curr % 10 == 9 || curr + 1 > n)
					curr /= 10;
				++curr;
			}
		}
		return ans;
	}
};

class Solution {
public:
	vector<int> lexicalOrder(int n) {
		vector<int> ans(n);
		int i = 0;

		auto dfs = [&](this auto&&dfs, int x) -> void {
			if (x > n) {
				return;
			}

			int unit = x % 10;
			int up_bound = 9 - unit;
			for (int k = 0; k <= up_bound; k++ ) {
				if (x + k > n) {
					break;
				}

				ans[i++] = x + k;
				dfs((x + k) * 10);
			}
		};
		dfs(1);
		return ans;
	}
};