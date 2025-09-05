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
    for (int d = 1; d * d <= n; d++) {
        if (n % d)
            continue;
        int k1 = d;
        int k2 = n / d;

        auto f = [&](int k) -> bool {
            int g = 0;
            for (int i = k; i < n; i++) {
                g = gcd(g, abs(a[i] - a[i - k]));
                if (g == 1)
                    return false;
            }
            return g != 1;
        };

        if (f(k1))
            ans++;
        if (k2 != k1 && f(k2))
            ans++;
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
