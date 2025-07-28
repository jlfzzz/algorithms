#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 10;
int t, n, l[maxn], r[maxn], pre[maxn], cnt[maxn];

void init() {
	for (int i = 1; i <= 2 * n; i++) cnt[i] = 0;
}

int main() {
	cin >> t;
	while (t--) {
		cin >> n;
		init();
		for (int i = 1; i <= n; i++) {
			cin >> l[i] >> r[i];
			if (l[i] == r[i]) cnt[l[i]]++;
		}
		for (int i = 1; i <= 2 * n; i++) {
			pre[i] = pre[i - 1] + (cnt[i] > 0);
		}
		for (int i = 1; i <= n; i++) {
			int k = pre[r[i]] - pre[l[i] - 1];
			if (l[i] == r[i] && cnt[l[i]] == 1) k--;
			if (k == r[i] - l[i] + 1) cout << "0";
			else cout << "1";
		}
		cout << "\n";
	}
	return 0;
}
