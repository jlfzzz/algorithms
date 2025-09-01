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
    int n, m;
    cin >> n >> m;
    vector<int> a(n + m + 1), b(n + m + 1), id(n + m + 1);
    For(i, n + m + 1) cin >> a[i];
    For(i, n + m + 1) cin >> b[i];

    int ca = 0, cb = 0, cnt = 0;
    for (int i = 0; i < n + m; i++) {
        int t1 = a[i], t2 = b[i];
        if (t1 > t2) {
            if (ca < n) {
                ca++;
                id[i] = 1;
                cnt += t1;
            } else {
                cb++;
                id[i] = 2;
                cnt += t2;
            }
        } else {
            if (cb < m) {
                cb++;
                id[i] = 2;
                cnt += t2;
            } else {
                ca++;
                id[i] = 1;
                cnt += t1;
            }
        }
    }

    vector<int> ans(n + m + 1);
    ans[n + m] = cnt;
    int bad1 = n + m, bad2 = n + m;
    vector<int> dp(n + m + 1);

    for (int i = n + m - 1; i >= 0; i--) {
        int t1 = a[i], t2 = b[i];
        int curr_id = id[i];

        if (curr_id == 1) {
            if (bad1 == n + m) {
                dp[i] = max(dp[i], a[n + m]);
            } else {
                dp[i] = max(dp[bad1] + a[bad1] - b[bad1], dp[i]);
            }
        } else {
            if (bad2 == n + m) {
                dp[i] = max(dp[i], b[n + m]);
            } else {
                dp[i] = max(dp[bad2] + b[bad2] - a[bad2], dp[i]);
            }
        }


        if (curr_id == 2 && t1 > t2) {
            bad1 = i;
        }

        if (curr_id == 1 && t2 > t1) {
            bad2 = i;
        }
    }

    for (int i = 0; i < m + n; i++) {
        int t1 = a[i], t2 = b[i];
        int curr_id = id[i];
        int t = cnt;
        if (curr_id == 1) {
            t -= t1;
        } else {
            t -= t2;
        }
        ans[i] = t + dp[i];
    }

    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
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
