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

int pow2[65];

void init() {
    pow2[0] = 1;
    for (int i = 1; i < 60; i++) {
        pow2[i] = 2 * pow2[i - 1];
    }
}
const double eps = 1e-9;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    For(i, n) cin >> a[i];

    vector<int> b(n, 0);
    int ans = 0;
    for (int i = 1; i < n; i++) {
        int x = a[i];
        int y = a[i - 1];

        if (x == 1 && y > 1) {
            cout << -1 << '\n';
            return;
        }

        int need = 0;
        int t = x;
        while (t < y) {
            i128 v = (i128) t * (i128) t;
            t = (int) v;
            need++;
        }

        int f = y;
        while (f != 1) {
            i128 v = (i128) f * (i128) f;
            if (v > (i128) t)
                break;
            f = (int) v;
            need--;
        }

        b[i] = b[i - 1] + need;
        if (b[i] < 0)
            b[i] = 0;
        ans += b[i];
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
