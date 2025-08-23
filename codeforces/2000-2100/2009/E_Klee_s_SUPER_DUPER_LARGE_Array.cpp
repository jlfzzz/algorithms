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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n, k;
    cin >> n >> k;

    int l = k, r = k + n;
    int sum = (k + k + n - 1) * n / 2;
    int ans = sum;
    while (l < r) {
        int m = l + (r - l) / 2;

        int left = (k + m) * (m - k + 1) / 2;
        int right = sum - left;
        ans = min(ans, abs(left - right));

        if (left <= right) {
            l = m + 1;
        } else {
            r = m;
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
