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
    For(i, n) { cin >> a[i]; }

    vector<int> dp(n + 1);
    vector<int> nxt(n + 1);
    map<int, int> mp;
    for (int i = n - 1; i >= 0; i--) {
        int x = a[i];
        if (mp.contains(x)) {
            nxt[i] = mp[x];
        }
        mp[x] = i;
    }
    map<int, pii> cnt;
    for (int i = 1; i <= n; i++) {
        int x = a[i - 1];
        dp[i] = dp[i - 1];

        if (x == 1) {
            dp[i]++;
            continue;
        }

        if (cnt.contains(x)) {
            auto [last, have] = cnt[x];
            // cout << "i is " << i << endl;
            // cout << x << endl;

            if (have + 1 == x) {
                // cout << dp[i] << endl;

                dp[i] = max(dp[i], dp[last - 1] + x);
                cnt[x].first = nxt[last - 1] + 1;
            } else {
                cnt[x].second++;
            }
        } else {
            cnt[x] = {i, 1};
        }
    }
    cout << dp[n] << '\n';
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
