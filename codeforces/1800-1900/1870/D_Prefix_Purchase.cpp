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
    vector<int> c(n);
    For(i, n) cin >> c[i];

    int k;
    cin >> k;

    vector<int> s(n);
    s[n - 1] = c[n - 1];
    for (int i = n - 2; i >= 0; i--)
        s[i] = min(s[i + 1], c[i]);

    vector<int> ans(n, 0);
    int a1 = k / s[0];
    int rem = k - a1 * s[0];
    ans[0] = a1;
    for (int i = 1; i < n; i++) {
        int d = s[i] - s[i - 1];
        if (d == 0) {
            ans[i] = ans[i - 1];
        } else {
            int can = min(ans[i - 1], rem / d);
            ans[i] = can;
            rem -= can * d;
        }
    }

    for (int x: ans) {
        cout << x << ' ';
    }
    cout << '\n';
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
