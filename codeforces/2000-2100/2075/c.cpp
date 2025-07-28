#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int N = 200005;
int cnt[N], sum[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		vector<int> a(m);
		fill(cnt, cnt + n + 2, 0);

		for (int i = 0; i < m; ++i) {
			cin >> a[i];
			cnt[a[i]]++;
		}

		// 构造后缀和 sum[i] 表示有多少个 a[j] ≥ i
		sum[n + 1] = 0;
		for (int i = n; i >= 0; --i) {
			sum[i] = sum[i + 1] + cnt[i];
		}

		ll ans = 0;
		for (int k = 1; k < n; ++k) {
			int x = sum[k]; // 颜色数 ≥ k
			int y = sum[n - k]; // 颜色数 ≥ n-k
			int z = sum[max(k, n - k)]; // 重复的颜色
			ans += 1LL * x * y - z;
		}

		cout << ans << '\n';
	}
	return 0;
}
