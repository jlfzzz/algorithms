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
    string s;
    cin >> s;
    int n = s.size();
    int ans = 0;

    for (int d = 1; d <= n / 2; ++d) {
        int cnt = 0;
        for (int i = 0; i + d < n; ++i) {
            if (s[i] == s[i + d] || s[i] == '?' || s[i + d] == '?')
                cnt++;
            if (i - d >= 0 && (s[i - d] == s[i] || s[i - d] == '?' || s[i] == '?'))
                cnt--;
            if (cnt == d)
                ans = 2 * d;
        }
    }

    cout << ans << "\n";
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
