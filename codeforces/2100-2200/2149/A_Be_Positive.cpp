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
    int c0 = 0;
    int c_neg = 0;
    int mn = -inf;
    For(i, n) {
        if (a[i] == 0) {
            c0++;
        } else if (a[i] < 0) {
            c_neg++;
            mn = max(mn, a[i]);
        }
    }

    ans = c0;
    if (c_neg % 2 == 1) {
        ans += -mn + 1;
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
