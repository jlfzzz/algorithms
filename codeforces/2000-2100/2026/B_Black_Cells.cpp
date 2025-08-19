#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1); // 1-indexed
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    if (n % 2 == 0) {
        // 偶数：相邻配对
        int ans = 0;
        for (int i = 2; i <= n; i += 2) {
            ans = max(ans, a[i] - a[i - 1]);
        }
        cout << ans << '\n';
    } else {
        // 奇数：枚举不参与配对的位置i（只能是奇数位置）
        int ans = 1e18;
        for (int i = 1; i <= n; i += 2) {
            int mx = 0;
            // 左半部分配对
            for (int j = 1; j < i; j += 2) {
                mx = max(mx, a[j + 1] - a[j]);
            }
            // 右半部分配对
            for (int j = i + 1; j <= n; j += 2) {
                mx = max(mx, a[j + 1] - a[j]);
            }
            ans = min(ans, mx);
        }
        cout << max(1LL, ans) << '\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
