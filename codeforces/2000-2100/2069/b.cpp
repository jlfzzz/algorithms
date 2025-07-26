#include <bits/stdc++.h>
using namespace std;
int flag[490005];
int a[705][705];

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		int maxn = 0;
		for (int i = 1; i <= n * m; i++) flag[i] = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> a[i][j];
				flag[a[i][j]] = 1, maxn = 1;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 2; j <= m; j++) {
				if (a[i][j] == a[i][j - 1]) flag[a[i][j]] = 2, maxn = 2;
			}
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 2; j <= n; j++) {
				if (a[j][i] == a[j - 1][i]) flag[a[j][i]] = 2, maxn = 2;
			}
		}
		int ans = 0;
		for (int i = 1; i <= n * m; i++) ans += flag[i];
		cout << ans - maxn << endl;
	}
	return 0;
}
