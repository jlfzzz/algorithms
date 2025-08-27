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

    auto query = [&](int pos) {
        cout << "throw " << pos << endl;
        int t;
        cin >> t;
        return t;
    };

    auto Swap = [&](int pos) { cout << "swap " << pos << endl; };

    vector<int> ans(n + 1);
    vector<int> dp(n + 3);
    dp[n + 1] = dp[n + 2] = 0;
    for (int i = n; i >= 1; i--) {
        if (dp[i + 1] != dp[i + 2]) {
            int t = query(i);
            if (t == dp[i + 1] + 1) {
                ans[i] = 1;
            } else {
                ans[i] = 2;
            }
            dp[i] = t;
        } else {
            if (i == 1) {
                Swap(i);
                int j = i + 1;
                int t = query(j);
                if (t == dp[j + 1] + 1) {
                    ans[i] = 1;
                } else {
                    ans[i] = 2;
                }
            } else {
                // cout << "cnm\n";
                int j = i - 1;
                int t = query(j);
                if (t == dp[i + 1] + 1) {
                    ans[j] = 2;
                } else {
                    ans[j] = 1;
                }
                // cout << ans[j] << "cnm" << endl;
                // dp[j] = t;
                dp[i] = 1 + dp[i + ans[j]];
                Swap(j);
                t = query(j);
                if (t == dp[i] + 1) {
                    ans[i] = 1;
                } else {
                    ans[i] = 2;
                }
                dp[j] = t;
                i = j;
            }
        }
    }

    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    cout << endl;
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
