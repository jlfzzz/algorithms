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
    int k, l1, r1, l2, r2;
    cin >> k >> l1 >> r1 >> l2 >> r2;

    i128 p = 1;
    int ans = 0;
    while (true) {
        i128 L = (l2 + p - 1) / p;
        i128 R = r2 / p;
        if (L > R)
            break;
        int LL = max((i128) l1, L);
        int RR = min((i128) r1, R);
        if (LL <= RR)
            ans += RR - LL + 1;

        if (p > r2 / k)
            break;
        p *= k;
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
