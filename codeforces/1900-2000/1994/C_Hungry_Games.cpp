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
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> dp(n + 1);
    int r = n;
    int sum = 0;
    for (int l = n - 1; l >= 0; l--) {
        sum += a[l];
        if (sum <= x) {
            dp[l] = dp[l + 1] + 1;
        } else {
            sum = 0;
            dp[l] = dp[l + 1];
        }
    }
    int ans = 0;
    for (int x: dp) {
        ans += x;
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
