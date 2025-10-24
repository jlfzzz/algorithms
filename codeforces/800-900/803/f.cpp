#include "bits/stdc++.h"
using namespace std;
using ll = long long;

constexpr ll MOD = 1000000007;
constexpr int MAXN = 100005;

ll pow2[MAXN];
int cnt[MAXN];

void solve() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	memset(cnt, 0, sizeof(cnt));
	int mx = 0;
	for (int x: nums) {
		cnt[x] += 1;
		mx = max(mx, x);
	}

	vector<ll> ans(mx + 1, 0);

	for (int i = mx; i >= 1; i--) {
		ll t = 0;
		for (int j = i; j <= mx; j += i) {
			t += cnt[j];
		}
		ans[i] = pow2[t] - 1;
		for (int j = i * 2; j <= mx; j += i) {
			ans[i] = (ans[i] + MOD - ans[j]) % MOD;
		}
	}
	cout << ans[1] << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	// 修复循环边界
	pow2[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pow2[i] = pow2[i - 1] * 2 % MOD;
	}

	solve();
}