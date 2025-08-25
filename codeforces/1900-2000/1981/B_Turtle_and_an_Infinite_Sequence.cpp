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
    int a, b;
    cin >> a >> b;
    if (b == 0) {
        cout << a << '\n';
    } else {
        int ans = a;
        for (int i = 30; i >= 0; --i)
            if ((a + b) >> i & 1 || max(0ll, a - b) >> i & 1 || (a + b - max(0ll, a - b) >= (1 << i)))
                ans |= (1 << i);
        cout << ans << '\n';
    }
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
