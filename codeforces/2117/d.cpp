//
// Created by 123 on 25-7-17.
//
#include "bits/stdc++.h"
using namespace std;
using ll = long long;

void solve() {
	int n;
	cin >> n;

	vector<long long> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	// 检查相邻元素差值是否形成等差数列
	// 操作1使差值减1，操作2使差值加1
	// 所以最终所有相邻差值应该相等

	// 计算目标差值（最终状态下相邻元素应该都是0，所以差值应该是0）
	// 但我们需要检查当前差值是否能通过操作调整到0

	bool possible = true;

	// 检查是否存在解
	// 设进行x次操作1，y次操作2
	// 对于位置i: a[i] - x*i - y*(n-i+1) = 0
	// 即: a[i] = x*i + y*(n-i+1)

	// 对于位置0: a[0] = x*1 + y*n
	// 对于位置1: a[1] = x*2 + y*(n-1)
	// 解这个方程组得到x和y

	// a[0] = x + y*n
	// a[1] = 2*x + y*(n-1)
	// 从第二个方程减去第一个方程: a[1] - a[0] = x - y
	// 所以: x = a[1] - a[0] + y
	// 代入第一个方程: a[0] = (a[1] - a[0] + y) + y*n = a[1] - a[0] + y*(n+1)
	// 所以: y = (a[0] - a[1] + a[0])/(n+1) = (2*a[0] - a[1])/(n+1)

	if ((2*a[0] - a[1]) % (n + 1) != 0) {
		cout << "NO\n";
		return;
	}

	long long y = (2*a[0] - a[1]) / (n + 1);
	long long x = a[1] - a[0] + y;

	// 检查x和y是否为非负整数
	if (x < 0 || y < 0) {
		cout << "NO\n";
		return;
	}

	// 验证这个解是否对所有元素都成立
	for (int i = 0; i < n; i++) {
		if (a[i] != x * (i + 1) + y * (n - i)) {
			possible = false;
			break;
		}
	}

	cout << (possible ? "YES" : "NO") << "\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}
