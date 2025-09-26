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

int vals[5] = {1, 10, 100, 1000, 10000};

void solve() {
    string s;
    cin >> s;
    int n = s.size();

    ranges::reverse(s);
    vector<int> dp1(6, 0), dp2(6, 0);
    for (int i = 0; i < n; i++) {
        char c = s[i];
        int cur = c - 'A';

        vector<int> ndp1(6, -inf), ndp2(6, -inf);

        for (int j = 0; j < 5; j++) {
            {
                int sgn = j > cur ? -1 : 1;
                int mx = max(cur, j);
                int val = sgn * vals[cur];
                ndp1[mx] = max(ndp1[mx], dp1[j] + val);
                ndp2[mx] = max(ndp2[mx], dp2[j] + val);
            }

            for (int k = 0; k < 5; k++) {
                int sgn = j > k ? -1 : 1;
                int mx = max(k, j);
                int val = sgn * vals[k];
                ndp2[mx] = max(ndp2[mx], dp1[j] + val);
            }
        }

        dp1.swap(ndp1);
        dp2.swap(ndp2);
    }

    int ans = max(ranges::max(dp1), ranges::max(dp2));

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
