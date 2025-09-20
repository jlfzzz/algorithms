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
    vector<int> r(n);
    For(i, n) cin >> r[i];

    vector<int> dp(m + 1, -1);
    dp[0] = 0;
    vector<int> d1(m + 1), d2(m + 1);

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (r[i] > 0) {
            d1[r[i]]++;
        } else if (r[i] < 0) {
            d2[-r[i]]++;
        } else {
            vector<int> prefI(m + 1), prefS(m + 1);
            for (int j = 1; j <= m; j++) {
                prefI[j] = prefI[j - 1] + d1[j];
                prefS[j] = prefS[j - 1] + d2[j];
            }
            for (int j = 0; j <= cnt; j++)
                if (dp[j] != -1) {
                    int str = j;
                    int intel = cnt - j;
                    if (intel > m)
                        intel = m;
                    dp[j] += prefI[intel] + prefS[str];
                }
            fill(d1.begin(), d1.end(), 0);
            fill(d2.begin(), d2.end(), 0);

            cnt++;
            vector<int> temp(m + 1, -1);
            for (int j = 0; j <= cnt; j++) {
                if (j > 0 && dp[j - 1] != -1)
                    temp[j] = max(temp[j], dp[j - 1]);
                if (dp[j] != -1)
                    temp[j] = max(temp[j], dp[j]);
            }
            dp.swap(temp);
        }
    }

    vector<int> prefI(m + 1), prefS(m + 1);
    for (int j = 1; j <= m; j++) {
        prefI[j] = prefI[j - 1] + d1[j];
        prefS[j] = prefS[j - 1] + d2[j];
    }
    for (int j = 0; j <= cnt; j++)
        if (dp[j] != -1) {
            int str = j;
            int intel = cnt - j;
            if (intel > m)
                intel = m;
            dp[j] += prefI[intel] + prefS[str];
        }

    int ans = *max_element(dp.begin(), dp.end());
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
