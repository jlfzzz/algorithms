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
const ll MOD2 = 4611686018427387847;
constexpr long long inf = 0x3f3f3f3f3f3f3f3f / 2;

void init() {}

void solve() {
    int n;
    cin >> n;

    string s(n + 1, '0');
    cout << '?' << ' ' << 1 << ' ' << n << endl;
    int x;
    cin >> x;
    int pre = x;

    if (x == 0) {
        cout << "! IMPOSSIBLE" << endl;
        return;
    }

    for (int i = n - 1; i >= 2; i--) {
        cout << '?' << ' ' << 1 << ' ' << i << endl;
        int x;
        cin >> x;
        if (pre == x) {
            s[i + 1] = '0';
        } else {
            s[i + 1] = '1';
        }

        // if (x == 0 && i != 1) {
        //     cout << "! IMPOSSIBLE" << endl;
        //     return;
        // }
    }
    s[1] = '0';
    s = s.substr(1);
    cout << "! " << s << '\n';
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
