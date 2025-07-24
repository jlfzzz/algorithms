#include<bits/stdc++.h>
using namespace std;

constexpr int N = 5e3 + 5;
int all_gcd[N][N];

// dp 刷表法求转移gcd所需最少次数

void solve() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	int g = nums[0];
	for (int i = 1; i < n; i++) {
		g = all_gcd[g][nums[i]];
	}

	int cnt = 0;
	for (int x: nums) {
		if (x == g) {
			cnt++;
		}
	}
	if (cnt) {
		cout << n - cnt << '\n';
		return;
	}

	int mx = ranges::max(nums);
	vector<vector<int> > dp(n + 1, vector<int>(mx + 1, INT_MAX / 2));
	//dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		int x = nums[i - 1];
		dp[i][x] = 1;
		for (int j = 0; j <= mx; j++) {
			if (dp[i - 1][j] == INT_MAX) continue;
			// 不选当前数
			dp[i][j] = min(dp[i][j], dp[i - 1][j]);
			// 选当前数，与当前 gcd 结合
			int t = all_gcd[x][j];
			dp[i][t] = min(dp[i][t], dp[i - 1][j] + 1);
		}
		// 单独选当前 x 作为一个 gcd 开始
	}

	cnt = dp[n][g];
	cout << cnt + n - 2 << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin >> t;
	memset(all_gcd, -1, sizeof(all_gcd));

	auto init = [&] {
		for (int i = 1; i <= N - 2; i++) {
			for (int j = 1; j <= N - 2; j++) {
				all_gcd[i][j] = gcd(i, j);
			}
		}
	};

	init();

	while (t--) {
		solve();
	}
}


// const int N = 5e3 + 5;
// int n, a[N];
// int dp[N][N];
// int g[N][N];
//
// int gc(int x, int y) { return g[x][y]; }

// 整个数组的gcd就是所有数取gcd
// dp求一个数组转成有一个是1的最小操作数

// int main() {
// 	ios::sync_with_stdio(0);
// 	cin.tie(0);
// 	for (int i = 0; i <= N - 5; i++) for (int j = 0; j <= N - 5; j++) g[i][j] = gcd(i, j);
// 	int T;
// 	cin >> T;
// 	while (T--) {
// 		cin >> n;
// 		for (int i = 1; i <= n; i++) cin >> a[i];
// 		int g = 0;
// 		for (int i = 1; i <= n; i++) g = gc(g, a[i]);
// 		for (int i = 1; i <= n; i++) a[i] /= g;
// 		sort(a + 1, a + n + 1);
// 		if (a[1] == 1) {
// 			int cnt = 0;
// 			for (int i = 1; i <= n; i++) cnt += a[i] > 1;
// 			cout << cnt << '\n';
// 			continue;
// 		}
// 		for (int i = 0; i <= n; i++) for (int j = 1; j <= N - 5; j++) dp[i][j] = 1e9;
// 		for (int i = 1; i <= n; i++) {
// 			for (int j = 0; j <= N - 5; j++) dp[i][j] = dp[i - 1][j];
// 			// 刷表
// 			for (int j = 0; j <= N - 5; j++) {
// 				dp[i][gc(a[i], j)] = min(dp[i][gc(a[i], j)], dp[i - 1][j] + 1);
// 			}
// 		}
// 		// i=1的时候，去和dp[0][j]转移的时候，这边多加了一个1，所以最后答案减1，是（n-1)-1
// 		cout << dp[n][1] + n - 2 << '\n';
// 	}
// 	return 0;
// }
