#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    For(i, n) { cin >> a[i + 1]; }

    int cnt = 0;
    int l = 1, r = 1;

    for (int i = 1; i <= n; i++) {
        int t = 0;
        for (int j = i; j <= n; j++) {
            if (a[j] < a[i]) {
                t += 1;
            } else if (a[j] > a[i]) {
                t -= 1;
            }

            if (t > cnt) {
                cnt = t;
                l = i, r = j;
            }
        }
    }

    cout << l << ' ' << r << '\n';

    // int left = a[l];
    // for (int i = l; i <= r - 1; i++) {
    //     a[i] = a[i + 1];
    // }
    // a[r] = left;

    // int ans = 0;
    // for (int i = 1; i <= n; i++) {
    //     for (int j = i + 1; j <= n; j++) {
    //         if (a[i] > a[j])
    //             ans++;
    //     }
    // }
    // cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cin >> T;
    while (T--)
        solve();
    return 0;
}
