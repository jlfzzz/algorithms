#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N = 100;
const int mod = 1e9 + 7;
int T, n, m, a[N];

signed main() {
	cin.tie(0)->ios::sync_with_stdio(0);
	cin >> T;
	while (T--) {
		cin >> n;
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			ans += a[i];
		}
		if (n == 1) {
			cout << ans << "\n"; //不能进行1，2操作
			continue;
		}
		while (n) {
			n--;
			for (int i = 1; i <= n; i++) {
				a[i] = a[i + 1] - a[i]; //2操作
			}
			int sum = 0;
			for (int i = 1; i <= n; i++) sum += a[i];
			ans = max(ans, max(sum, -sum)); //是否进行1操作
		}
		cout << ans << "\n";
	}
	return 0;
}
