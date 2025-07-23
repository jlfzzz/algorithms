#include<bits/stdc++.h>
using namespace std;

const int N = 5e3 + 5;
int n, a[N];
int dp[N][N];
int g[N][N];

int gc(int x, int y) { return g[x][y]; }

// 整个数组的gcd就是所有数取gcd
// dp求一个数组转成有一个是1的最小操作数

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	for (int i = 0; i <= N - 5; i++) for (int j = 0; j <= N - 5; j++) g[i][j] = gcd(i, j);
	int T;
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		int g = 0;
		for (int i = 1; i <= n; i++) g = gc(g, a[i]);
		for (int i = 1; i <= n; i++) a[i] /= g;
		sort(a + 1, a + n + 1);
		if (a[1] == 1) {
			int cnt = 0;
			for (int i = 1; i <= n; i++) cnt += a[i] > 1;
			cout << cnt << '\n';
			continue;
		}
		for (int i = 0; i <= n; i++) for (int j = 1; j <= N - 5; j++) dp[i][j] = 1e9;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j <= N - 5; j++) dp[i][j] = dp[i - 1][j];
			// 刷表
			for (int j = 0; j <= N - 5; j++) {
				dp[i][gc(a[i], j)] = min(dp[i][gc(a[i], j)], dp[i - 1][j] + 1);
			}
		}
		// i=1的时候，去和dp[0][j]转移的时候，这边多加了一个1，所以最后答案减1，是（n-1)-1
		cout << dp[n][1] + n - 2 << '\n';
	}
	return 0;
}
