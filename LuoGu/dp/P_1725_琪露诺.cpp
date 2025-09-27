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
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n + 1);
    For(i, n + 1) cin >> a[i];

    vector<int> dp(n + 1, -inf);
    dp[0] = 0;
    int L = 0, R = 0;
    multiset<int> st;

    for (int i = 1; i <= n; i++) {
        while (i - R >= l) {
            st.insert(dp[R]);
            R++;
        }
        while (i - L > r) {
            st.erase(st.find(dp[L]));
            L++;
        }

        if (st.empty()) {
            continue;
        }
        auto it = st.rbegin();
        dp[i] = *it + a[i];
    }

    int ans = -inf;
    for (int i = n; i >= max(0ll, n - r + 1); i--) {
        ans = max(ans, dp[i]);
    }
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
