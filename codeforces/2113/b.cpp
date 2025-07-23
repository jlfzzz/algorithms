#include "bits/stdc++.h"
using namespace std;
int T, w, h, a, b, x1, yy1, x2, y2;

int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> w >> h >> a >> b >> x1 >> yy1 >> x2 >> y2;
		if (x1 == x2) cout << (abs(y2 - yy1) % b ? "No\n" : "Yes\n");
		else if (yy1 == y2) cout << (abs(x2 - x1) % a ? "No\n" : "Yes\n");
		else cout << ((abs(x2 - x1) % a && abs(y2 - yy1) % b) ? "No\n" : "Yes\n");
	}
	return 0;
}
