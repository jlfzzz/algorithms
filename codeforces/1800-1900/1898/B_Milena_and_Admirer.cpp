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

    int suf_mn = inf;
    int ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] > suf_mn) {
            if (a[i] % suf_mn == 0) {
                ans += a[i] / suf_mn - 1;
            } else {
                int t = a[i] / suf_mn;
                ans += t;
                suf_mn = a[i] / (t + 1);
            }

        } else {
            suf_mn = a[i];
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
