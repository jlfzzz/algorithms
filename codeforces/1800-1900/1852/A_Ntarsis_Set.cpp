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

    vector<int> a(n);
    For(i, n) cin >> a[i];

    if (a[0] != 1) {
        cout << 1 << '\n';
        return;
    }

    int lo = 0;
    int hi = n * k + 10000;

    auto check = [&](int m) -> bool {
        int t = m;
        int pos = n - 1;
        for (int i = 0; i < k; i++) {
            while (pos >= 0 && a[pos] > t) {
                pos--;
            }

            t -= pos + 1;
        }
        return t > 0;
    };

    int ans = 0;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            ans = mid;
            hi = mid;
        } else {
            lo = mid + 1;
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
