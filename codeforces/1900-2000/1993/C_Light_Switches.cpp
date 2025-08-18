#include <bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

const int N = 2e5 + 10;
int T;
int n, k, a[N];

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> k;
        int maxx = -1;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            maxx = max(a[i], maxx);
        }
        int l = maxx, r = maxx + k - 1;
        for (int i = 1; i <= n; i++) {
            int tmp = (maxx - a[i]) / k;
            if (tmp & 1)
                l = max(l, a[i] + k * (tmp + 1));
            else
                r = min(r, a[i] + k * (tmp + 1) - 1);
        }
        if (r < l)
            cout << -1 << endl;
        else
            cout << l << endl;
    }
    return 0;
}
