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
    int g = a[0];
    for (int i = 1; i < n; i++) {
        g = gcd(g, a[i]);
    }

    vector<int> v;
    if (n > 1) {
        for (int i = 0; i < n; i++) {
            v.push_back(i * g);
        }
    } else {
        v.push_back(g);
    }

    int lo = 0;
    int hi = 2e9 + 1;
    int ans = lo;

    while (lo < hi) {
        int mid = (lo + hi) / 2;
        auto check = [&](int target) -> int {
            int i = ranges::upper_bound(v, target - 1) - v.begin();

            return i >= target - k + 1;
        };
        if (check(mid)) {
            lo = mid + 1;
            ans = mid;
        } else {
            hi = mid;
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
