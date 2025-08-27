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
    vector<int> a(n + 1);
    For(i, n) cin >> a[i + 1];

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i & 1) {
            if (i + 1 <= n) {
                if (a[i] > a[i + 1]) {
                    ans += a[i] - a[i + 1];
                    a[i] = a[i + 1];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i & 1) {
            if (i + 2 <= n) {
                int x = a[i], y = a[i + 1], z = a[i + 2];
                if (x + z > y) {
                    int d = min(z, x + z - y);
                    ans += d, z -= d;
                    if (x + z > y) {
                        int d2 = x + z - y;
                        x -= d2;
                        ans += d2;
                    }
                    a[i] = x, a[i + 1] = y, a[i + 2] = z;
                }
            }
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
