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
    string s1, s2;
    cin >> s1 >> s2;

    int pos = -1;
    string ans;

    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            char c1 = s1[i + 1];
            char c2 = s2[i];
            if (c1 == '1' && c2 == '0') {
                ans = s1.substr(0, i + 1) + s2.substr(i);
                pos = i;
                break;
            }
        } else {
            pos = i;
            ans = s1 + s2[n - 1];
        }
    }

    int cnt = 1;
    if (pos == n - 1) {
        for (int j = n - 2; j >= 0; --j) {
            if (s1[j + 1] == s2[j]) cnt++;
            else break;
        }
    } else {
        for (int j = pos - 1; j >= 0; --j) {
            if (s1[j + 1] == s2[j]) cnt++;
            else break;
        }
    }

    cout << ans << '\n' << cnt << '\n';
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
