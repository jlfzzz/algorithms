#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define i128 __int128_t
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ull unsigned long long
#define For(i, n) for (int(i) = 0; (i) < (n); (i) += 1)
constexpr int MOD = int(1e9 + 7);
const ll MOD2 = 4611686018427387847;
#define int ll
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    string s;
    cin >> s;

    int n = s.size();
    double ans = 0.0;

    for (int i = 0; i < n; i++) {
        if (s[i] == 't') {
            int cnt = 1;
            for (int j = i + 1; j < n; j++) {
                if (s[j] == 't') {
                    cnt++;
                }
                if (s[j] == 't' and cnt >= 3) {
                    ans = max(ans, 1.0 * (cnt - 2) / ((j - i + 1) - 2));
                }
            }
        }
    }
    cout << fixed << setprecision(20) << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
        solve();
    return 0;
}
