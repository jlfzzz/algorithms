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
    string s;
    cin >> s;


    if (n == 2) {
        cout << stoi(s) << '\n';
        return;
    }

    if (n == 3) {
        int t1 = stoi(s.substr(0, 2));
        int t2 = stoi(s.substr(2));

        int ans = inf;
        ans = min(ans, t1 + t2);
        ans = min(ans, t1 * t2);

        t1 = stoi(s.substr(1, 2));
        t2 = stoi(s.substr(0, 1));

        ans = min(ans, t1 + t2);
        ans = min(ans, t1 * t2);

        cout << ans << '\n';
        return;
    }

    int ans = inf;
    for (char c: s) {
        if (c == '0') {
            cout << 0 << '\n';
            return;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        int t = stoi(s.substr(i, 2));
        for (int j = 0; j < i; j++) {
            if (s[j] != '1') {
                t += s[j] - '0';
            }
        }

        for (int j = i + 2; j < n; j++) {
            if (s[j] != '1') {
                t += s[j] - '0';
            }
        }

        ans = min(ans, t);
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
