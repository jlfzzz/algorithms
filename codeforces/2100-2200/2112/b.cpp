#include <bits/stdc++.h>
#define int long long

using namespace std;

const int kMaxN = 1010;

int a[kMaxN], t, n, ans;

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    for (cin >> t; t--;) {
        cin >> n, ans = -1;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i < n; i++) {
            ans = (abs(a[i] - a[i + 1]) <= 1 ? 0 : ans);
        }
        for (int i = 2; i < n; i++) {
            ans &= (a[i - 1] < a[i] && a[i] > a[i + 1]) || (a[i - 1] > a[i] && a[i] < a[i + 1]) ? 1 : -1;
        }
        cout << ans << '\n';
    }
    return 0;
}
