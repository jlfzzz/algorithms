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
    vector<int> cnt(61);
    For(i, n) cin >> a[i];
    for (int x: a) {
        for (int i = 0; i <= 60; i++) {
            if (x >> i & 1) {
                cnt[i]++;
            }
        }
    }

    int ans = 0;

    for (int i = 0; i <= 60; i++) {
        int x = cnt[i];
        int t = x / 2;

        if (t)
            ans += (1LL << i) * t;
    }
    ans *= 2;
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    while (T--)
        solve();
    return 0;
}
