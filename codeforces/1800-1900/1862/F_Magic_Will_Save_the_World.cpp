#include <bits/stdc++.h>
#include <vector>
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
    int w, f;
    cin >> w >> f;
    int n;
    cin >> n;

    vector<int> s(n + 1);
    For(i, n) cin >> s[i + 1];

    int total = accumulate(s.begin() + 1, s.end(), 0ll);

    int ans = 0;
    int lo = 1;
    int hi = 1e9 + 5;
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        auto check = [&](int time) -> bool {
            int s1 = w * time, s2 = f * time;
            if (s1 >= total || s2 >= total) {
                return true;
            }
            int lim = min(s1, total);
            // vector<int> dp(lim + 1, 0);
            // dp[0] = 1;

            bitset<1'000'005> dp;
            dp[0] = true;
            for (int i = 1; i <= n; i++) {
                // for (int j = lim; j >= s[i]; j--) {
                //     dp[j] |= dp[j - s[i]];
                // }
                dp |= dp << s[i];
            }
            for (int i = 0; i <= lim; i++) {
                if (dp[i]) {
                    int other = max(0ll, total - i);
                    if (other <= s2) {
                        return true;
                    }
                }
            }
            return false;
        };

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
