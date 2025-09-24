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

    if (n == 1) {
        cout << 0 << '\n';
        return;
    }

    vector<int> diff(n);
    For(i, n - 1) { diff[i] = a[i + 1] - a[i]; }


    int cnt = 0;
    for (int i = 0; i < n - 1; i++) {
        if (diff[i] <= 0) {
            cnt++;
        }
    }

    int cnt2 = 0;
    int ans = cnt;
    for (int i = 0; i < n - 1; i++) {
        if (diff[i] <= 0) {
            cnt--;
        }

        if (i > 0 && a[i] >= a[i - 1]) {
            cnt2++;
        }

        ans = min(ans, cnt2 + cnt + 1);
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
