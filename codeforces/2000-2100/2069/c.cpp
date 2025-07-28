#include <bits/stdc++.h>
using namespace std;

#define int long long
constexpr int MOD = 998244353;

// 快速输入输出 + 多组数据
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		int n;
		cin >> n;

		vector<int> a(n + 1);
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
		}

		int cnt1 = 0; // 当前遇到的 1 的个数
		int sum = 0; // 当前所有合法 1..2.. 的贡献（已乘以 2^cnt2）
		int ans = 0; // 最终答案

		for (int i = 1; i <= n; ++i) {
			if (a[i] == 1) {
				cnt1++;
			} else if (a[i] == 2) {
				sum = (sum * 2 % MOD + cnt1) % MOD;
			} else if (a[i] == 3) {
				ans = (ans + sum) % MOD;
			}
		}

		cout << ans << '\n';
	}

	return 0;
}
