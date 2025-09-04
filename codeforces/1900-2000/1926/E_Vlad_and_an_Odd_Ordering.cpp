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
    int n, k;
    cin >> n >> k;

    int ans = -1;
    if (k <= (n + 1) / 2) {
        ans = 2 * k - 1;
    } else {
        k -= (n + 1) / 2;
        int i = 2;
        while (k) {
            int cnt = (n - i + 1 + 2 * i - 1) / (i * 2);
            if (k > cnt) {
                k -= cnt;
            } else {
                int start = i, d = i + i;
                k--;
                start += k * d;
                ans = start;
                break;
            }

            i *= 2;
        }
    }

    cout << ans << endl;
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
