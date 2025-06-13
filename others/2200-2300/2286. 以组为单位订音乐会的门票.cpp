//
// Created by 123 on 25-6-12.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr int MOD = 1'000'000'007;
constexpr int DIR[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class BookMyShow {
public:
	int n, m;
	vector<int> mn;
	vector<long long> sum;

	void update(int o, int l, int r, int i, int val) {
		if (l == r) {
			mn[o] += val;
			sum[o] += val;
			return;
		}

		int m = (l + r) >> 1;
		if (i <= m) {
			update(o * 2, l, m, i, val);
		} else {
			update(o * 2 + 1, m + 1, r, i, val);
		}
		mn[o] = min(mn[o * 2], mn[o * 2 + 1]);
		sum[o] = sum[o * 2] + sum[o * 2 + 1];
	}

	long long query_sum(int o, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return sum[o];
		}
		long long res = 0;
		int m = (l + r) >> 1;
		if (L <= m) {
			res = query_sum(o * 2, l, m, L, R);
		}
		if (R > m) {
			res += query_sum(o * 2 + 1, m + 1, r, L, R);
		}
		return res;
	}

	int find_first(int o, int l, int r, int R, int val) {
		if (mn[o] > val) {
			return -1;
		}
		if (l == r) {
			return l;
		}
		int m = (l + r) >> 1;
		if (mn[o * 2] <= val) {
			return find_first(o * 2, l, m, R, val);
		}
		if (R > m) {
			return find_first(o * 2 + 1, m + 1, r, R, val);
		}
		return -1;
	}


	BookMyShow(int n, int m) : n(n), m(m), mn(4 << __lg(n)), sum(4 << __lg(n)) {
	}

	vector<int> gather(int k, int maxRow) {
		int r = find_first(1, 0, n - 1, maxRow, m - k);
		if (r < 0) {
			return {};
		}
		int c = query_sum(1, 0, n - 1, r, r);
		update(1, 0, n - 1, r, k);
		return {r, c};
	}

	bool scatter(int k, int maxRow) {
		long long s = query_sum(1, 0, n - 1, 0, maxRow);
		if (s > static_cast<long long>(m * (maxRow + 1) - k)) {
			return false;
		}
		int i = find_first(1, 0, n - 1, maxRow, m - 1);
		while (k) {
			int left = min(m - (int)query_sum(1, 0, n - 1, i, i), k);
			update(1, 0, n - 1, i, left);
			k -= left;
			i++;
		}
		return true;
	}
};
