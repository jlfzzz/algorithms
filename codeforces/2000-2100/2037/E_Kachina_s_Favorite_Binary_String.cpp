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
    bool f = false;
    int pos = -1;
    int pre = -1;

    for (int i = 2; i <= n; i++) {
        cout << '?' << ' ' << 1 << ' ' << i << endl;
        int t;
        cin >> t;
        if (t != 0) {
            s[i] = '1';
            for (int j = i - 1; j >= i - t; j--) {
                s[j] = '0';
            }

            for (int j = i - t - 1; j >= 1; j--) {
                s[j] = '1';
            }
            f = true;
            pos = i;
            pre = t;
            break;
        }
    }

    if (!f) {
        cout << "! IMPOSSIBLE" << endl;
        return;
    }

    for (int i = pos + 1; i <= n; i++) {
        cout << '?' << ' ' << 1 << ' ' << i << endl;
        int t;
        cin >> t;
        if (t != pre) {
            s[i] = '1';
            pre = t;
        }
    }
    s = s.substr(1);
    cout << "! " << s << endl;
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
