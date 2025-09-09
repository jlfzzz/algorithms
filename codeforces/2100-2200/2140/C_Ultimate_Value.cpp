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
    vector<int> a(n);
    For(i, n) cin >> a[i];

    int ans = 0;
    if (n & 1) {
        ans = n - 1;
    } else {
        ans = max(ans, n - 2);
    }

    map<int, int> pre, suf;

    int total = 0;
    for (int i = 0; i < n; i += 2) {
        if (i + 1 < n) {
            total += a[i] - a[i + 1];
        } else {
            total += a[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            int x = a[i];
            int y = 2 * x - i;
            suf[y]++;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            int x = a[i];
            int y = 2 * x - i;
            suf[y]--;
            if (suf[y] == 0) {
                suf.erase(y);
            }

            y = 2 * x + i;
            pre[y]++;
        } else {
            int x = a[i];

            if (!pre.empty()) {
                int y = 2 * x + i;
                ans = max(ans, y - pre.begin()->first);
            }
            if (!suf.empty()) {
                int y = 2 * x - i;
                ans = max(ans, y - suf.begin()->first);
            }
        }
    }

    cout << total + ans << '\n';
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
