#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
#define int ll
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int ans = 0;
    int pre = 0;

    for (int i = 1; i < n; i++) {
        int cur = a[i];
        int y = a[i - 1];

        if (cur >= y) {
            int cnt = 0;
            while (y * 2 <= cur) {
                cnt++;
                y *= 2;
            }

            pre = max(0ll, pre - cnt);
            ans += pre;
        } else {
            int cnt = 0;
            while (cur < y) {
                cnt++;
                cur *= 2;
            }

            pre += cnt;
            ans += pre;
        }
    }

    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
