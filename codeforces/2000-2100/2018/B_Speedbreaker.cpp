#include <bits/stdc++.h>
using namespace std;

int n, a[200005];
vector<int> idx[200005];

int main() {
    std::ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            idx[i].clear();
        int ans = n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            idx[a[i]].push_back(i);
        }
        int l = n + 1, r = 0, ll = 1, rr = n;
        for (int i = 1; i <= n; i++) {
            for (int x: idx[i]) {
                l = min(l, x);
                r = max(r, x);
            }
            // if (r - l + 1 > i) {
            //     ans = 0;
            //     break;
            // }
            if (l <= r) {
                ll = max(ll, r - i + 1);
                rr = min(rr, l + i - 1);
            }
        }
        if (ans == 0)
            cout << ans << "\n";
        else
            cout << max(rr - ll + 1, 0) << "\n";
    }
    return 0;
}
