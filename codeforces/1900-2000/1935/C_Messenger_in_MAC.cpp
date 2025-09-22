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
    int n, l;
    cin >> n >> l;
    struct Info {
        int a, b;
    };

    vector<Info> vi(n + 1);
    for (int i = 1; i <= n; i++) {
        int ai, bi;
        cin >> ai >> bi;
        vi[i] = {ai, bi};
    }

    sort(vi.begin() + 1, vi.begin() + n + 1, [](const Info &x, const Info &y) { return x.b < y.b; });

    int ans = 0;
    vector<int> dp(n + 1, inf);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        auto [cur_a, cur_b] = vi[i];
        if (cur_a <= l) {
            ans = max(ans, 1ll);
        }

        for (int j = n; j >= 2; j--) {
            if (dp[j - 1] == inf) {
                continue;
            }
            dp[j] = min(dp[j], dp[j - 1] + cur_a);
            if (dp[j] + cur_b <= l) {
                ans = max(ans, j);
            }
        }

        dp[1] = min(dp[1], cur_a - cur_b);
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
