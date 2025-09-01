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
    string s;
    cin >> s;

    auto f = [&](string &s) -> int {
        int cnt = 0;
        int left = 0;
        for (int i = 0; i < 2 * n; i++) {
            if (s[i] == 'A') {
                cnt += abs(left - i);
                left += 2;
            }
        }
        return cnt;
    };

    int ans = f(s);
    ranges::reverse(s);
    ans = min(ans, f(s));
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
