#include <bits/stdc++.h>
using namespace std;
int t, n, a[100010], b[100010];
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1); // 排序
    int ans = 0;
    for (int i = 1; i <= n; i++) { // 枚举折点
        int tmp = INT_MAX;
        for (int j = 1; j <= i; j++)
            tmp = min(tmp, abs(a[j] - b[n - i + j]));
        for (int j = i + 1; j <= n; j++)
            tmp = min(tmp, abs(a[j] - b[j - i]));
        ans = max(ans, tmp);
    }
    cout << ans << endl;
}
signed main() {
    cin >> t;
    while (t--)
        solve();
    return 0;
}
