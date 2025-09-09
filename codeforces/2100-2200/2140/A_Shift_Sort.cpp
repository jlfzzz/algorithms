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

    int c1 = 0;
    for (char c: s) {
        if (c == '1') {
            c1++;
        }
    }

    if (c1 == 0 || c1 == n) {
        cout << 0 << '\n';
        return;
    }

    int l = 0, r = n - 1;
    int ans = 0;
    while (l < r) {
        while (l < r && s[l] == '0')
            l++;
        if (l >= r) {
            break;
        }
        while (l < r && s[r] == '1')
            r--;
        if (l >= r) {
            break;
        }
        ans++;
        l++, r--;
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
