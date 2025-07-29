#include <bits/stdc++.h>
using namespace std;
#define N 300005
long long t, n, x, y, a[N], ans, sum;

int main() {
	cin >> t;
	while (t--) {
		cin >> n >> x >> y;
		sum = ans = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			sum += a[i];
		}

		sort(a + 1, a + n + 1);

		for (int i = 1; i <= n; i++) {
			long long l = sum - y - a[i];
			long long r = sum - x - a[i];

			long long pos1 = lower_bound(a + i + 1, a + n + 1, l) - a;
			long long pos2 = upper_bound(a + i + 1, a + n + 1, r) - a - 1;

			if (pos1 <= pos2) {
				ans += pos2 - pos1 + 1;
			}
		}

		cout << ans << endl;
	}
	return 0;
}
